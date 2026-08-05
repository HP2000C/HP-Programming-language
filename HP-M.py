# HP™ Programming language

import math
import random as rnd
import re
import sys
import os
from datetime import datetime, timedelta
import jdatetime
import time as tm

class ReturnException(Exception):
    def __init__(self, value):
        self.value = value

class Percent:
    def __init__(self, value):
        self.value = value / 100.0

    def apply(self, number):
        return number * self.value

    def __str__(self):
        return f"{self.value * 100}%"

    def __repr__(self):
        return str(self)

class SoloDate:
    def __init__(self, year, month, day, is_jalali=True):
        self.is_jalali = is_jalali
        if is_jalali:
            self.jalali_date = jdatetime.date(year, month, day)
            self.gregorian_date = self.jalali_date.togregorian()
        else:
            self.gregorian_date = datetime(year, month, day).date()
            self.jalali_date = jdatetime.date.fromgregorian(date=self.gregorian_date)

    def to_jalali_string(self):
        return self.jalali_date.strftime("%Y/%m/%d")

    def to_gregorian_string(self):
        return self.gregorian_date.strftime("%Y/%m/%d")

    def __sub__(self, other):
        if isinstance(other, SoloDate):
            return (self.gregorian_date - other.gregorian_date).days

    def __str__(self):
        return self.to_jalali_string()

    def year(self):
        return self.jalali_date.year if self.is_jalali else self.gregorian_date.year

    def month(self):
        return self.jalali_date.month if self.is_jalali else self.gregorian_date.month

    def day(self):
        return self.jalali_date.day if self.is_jalali else self.gregorian_date.day

    @staticmethod
    def today():
        today_greg = datetime.now().date()
        today_jalali = jdatetime.date.fromgregorian(date=today_greg)
        result = SoloDate(1, 1, 1)
        result.gregorian_date = today_greg
        result.jalali_date = today_jalali
        result.is_jalali = True
        return result

class SoloArray:
    def __init__(self, items=None):
        self.items = list(items) if items else []

    def get(self, index):
        return self.items[index - 1] if 1 <= index <= len(self.items) else None

    def set(self, index, value):
        if 1 <= index <= len(self.items):
            self.items[index - 1] = value
            return True
        return False

    def add(self, value):
        self.items.append(value)
        return self

    def remove(self, index):
        if 1 <= index <= len(self.items):
            del self.items[index - 1]
            return True
        return False

    def length(self):
        return len(self.items)

    def sum(self):
        return sum(item for item in self.items if isinstance(item, (int, float)))

    def avg(self):
        nums = [item for item in self.items if isinstance(item, (int, float))]
        return sum(nums) / len(nums) if nums else 0

    def min(self):
        nums = [item for item in self.items if isinstance(item, (int, float))]
        return min(nums) if nums else None

    def max(self):
        nums = [item for item in self.items if isinstance(item, (int, float))]
        return max(nums) if nums else None

    def __str__(self):
        return "[" + ", ".join(str(item) for item in self.items) + "]"

    def __repr__(self):
        return str(self)

    def __iter__(self):
        return iter(self.items)

class SoloDict:
    def __init__(self, pairs=None):
        self.data = {}
        if pairs:
            for k, v in pairs:
                self.data[k] = v

    def value(self, key):
        return self.data.get(key, None)

    def key(self, value):
        for k, v in self.data.items():
            if v == value:
                return k
        return None

    def add(self, key, value):
        self.data[key] = value
        return self

    def remove(self, key):
        if key in self.data:
            del self.data[key]
            return True
        return False

    def has(self, key):
        return key in self.data

    def keys(self):
        return SoloArray(list(self.data.keys()))

    def values(self):
        return SoloArray(list(self.data.values()))

    def length(self):
        return len(self.data)

    def __str__(self):
        items = []
        for k, v in self.data.items():
            k_str = f'"{k}"' if isinstance(k, str) else str(k)
            items.append(f'{k_str}:{v}')
        return "[" + "; ".join(items) + "]"

    def __repr__(self):
        return str(self)

def smart_convert(value):
    if not isinstance(value, str):
        return value
    value = value.strip()
    if value.lower() == 'null' or value == '':
        return None
    if value.lower() == 'true':
        return True
    if value.lower() == 'false':
        return False
    if value.endswith('%'):
        try:
            return Percent(float(value[:-1]))
        except:
            return value
    try:
        return int(value)
    except ValueError:
        pass
    try:
        return float(value)
    except ValueError:
        pass
    return value

class FunctionHandler:
    def __init__(self):
        self.keywords = {

    # Output
    "chap": "write",

    # Variables
    "set": "set",

    # Conditions
    "agar": "when",
    "vagarna": "else",

    # Loops
    "loop": "loop",
    "baraye": "for",
    "az": "from",
    "ta": "to",
    "gam": "step",
    "dar": "in",

    # Functions
    "tabe": "function",
    "bargard": "return",

    # Error handling
    "emtehan": "try",
    "khata": "error",
    "hamishe": "always",

    # Arrays
    "ezafeBe": "add_to",
    "hazfAz": "remove_from",

    # Flow control
    "shekan": "break",
    "edame": "continue",

    # Input
    "begir": "input",

    # Math
    "baghimande": "mod",

    # Built-in values
    "dorost": "true",
    "ghalat": "false",
    "hich": "null"
}
        self.functions = {}

    def define(self, name, params, body_lines, default_values=None):
        self.functions[name] = {
            'params': params,
            'body': body_lines,
            'defaults': default_values or {}
        }

    def call(self, name, args, executor):
        if name not in self.functions:
            return None
        func = self.functions[name]
        params = func['params']
        defaults = func['defaults']
        body = func['body']
        
        old_values = {}
        for param in params:
            if param in executor.variables:
                old_values[param] = executor.variables[param]
            else:
                old_values[param] = None
        
        for i, param in enumerate(params):
            if i < len(args):
                executor.set_variable(param, args[i])
            elif param in defaults:
                executor.set_variable(param, defaults[param])
            else:
                executor.set_variable(param, None)
        
        return_value = None
        lines = body.split('\n')
        
        try:
            executor._execute_block(lines, 0, len(lines) - 1)
        except ReturnException as e:
            return_value = e.value
        except Exception as e:
            executor.error(f"Error in function '{name}': {e}")
        
        for param in params:
            if old_values[param] is not None:
                executor.variables[param] = old_values[param]
            elif param in executor.variables:
                del executor.variables[param]
        
        return return_value

class HP:
    def translate(self, line):
        for hp, old in self.function_handler.keywords.items():
            line = re.sub(rf"\b{hp}\b", old, line, flags=re.IGNORECASE)
            return line
    
    def __init__(self):
        self.variables = {}
        self.colors = {
            'red': '\033[91m',
            'green': '\033[92m',
            'yellow': '\033[93m',
            'blue': '\033[94m',
            'purple': '\033[95m',
            'cyan': '\033[96m',
            'white': '\033[97m',
            'reset': '\033[0m'
        }
        self.function_handler = FunctionHandler()
        self.builtins = {
            'sqrt': lambda x: math.sqrt(float(x)),
            'int': lambda x: int(float(str(x))),
            'float': lambda x: float(str(x)),
            'str': lambda x: str(x),
            'bool': lambda x: bool(x),
            'abs': lambda x: abs(float(x)) if self._is_number(x) else 0
        }

    def set_variable(self, name, value):
        self.variables[name] = value

    def error(self, msg):
        print(f"{self.colors['red']}Error: {msg}{self.colors['reset']}")

    def color_text(self, text, color):
        return f"{self.colors.get(color, '')}{text}{self.colors['reset']}"

    def _is_number(self, v):
        return isinstance(v, (int, float))

    def _to_num(self, v):
        if isinstance(v, (int, float)):
            return v
        if isinstance(v, bool):
            return 1 if v else 0
        if isinstance(v, Percent):
            return v.value
        if isinstance(v, str):
            try:
                return float(v) if '.' in v else int(v)
            except:
                pass
        return v

    def _format_val(self, val):
        if val is None:
            return "null"
        if isinstance(val, bool):
            return "true" if val else "false"
        if isinstance(val, SoloDate):
            return val.to_jalali_string()
        if isinstance(val, Percent):
            return str(val)
        if isinstance(val, (SoloArray, SoloDict)):
            return str(val)
        return val

    def _evaluate_write_content(self, content):
        if not content:
            return ""
        val = self._evaluate_expression(content)
        return str(self._format_val(val))

    def _evaluate_expression(self, expr):
        expr = str(expr).strip()
        if not expr:
            return ""
        if expr.startswith('"') and expr.endswith('"'):
            return expr[1:-1]
        if expr.startswith("'") and expr.endswith("'"):
            return expr[1:-1]
        if expr.lower() == 'null':
            return None
        if expr.lower() == 'true':
            return True
        if expr.lower() == 'false':
            return False

        if expr.startswith('('):
            depth = 0
            close_idx = -1
            for i, ch in enumerate(expr):
                if ch == '(':
                    depth += 1
                elif ch == ')':
                    depth -= 1
                if depth == 0:
                    close_idx = i
                    break
            if close_idx == len(expr) - 1:
                return self._evaluate_expression(expr[1:-1])

        if expr.endswith('%') and not expr.startswith('$'):
            try:
                return Percent(float(expr[:-1]))
            except:
                pass

        if expr == '@today':
            return SoloDate.today()
        m = re.match(r'@(\d{4})/(\d{2})/(\d{2})$', expr)
        if m:
            return SoloDate(int(m[1]), int(m[2]), int(m[3]), True)
        m = re.match(r'@@(\d{4})/(\d{2})/(\d{2})$', expr)
        if m:
            return SoloDate(int(m[1]), int(m[2]), int(m[3]), False)

        if expr.endswith('!') and not expr.startswith('!!'):
            v = self._evaluate_expression(expr[:-1])
            try:
                num = int(v)
                if num < 0:
                    self.error("Factorial of negative is undefined")
                    return 0
                return math.factorial(num)
            except (ValueError, TypeError):
                self.error("Invalid factorial")
                return 0

        if expr.startswith('|') and expr.endswith('|'):
            v = self._evaluate_expression(expr[1:-1])
            if isinstance(v, (int, float)):
                return abs(v)
            self.error("abs error")
            return 0

        for func in ['sin', 'cos', 'tan']:
            m = re.match(rf'\${func}\((.+)\)$', expr)
            if m:
                v = self._evaluate_expression(m[1])
                if isinstance(v, (int, float)):
                    return getattr(math, func)(math.radians(v))
                self.error(f"{func} needs number")
                return 0

        m = re.match(r'\$log\((.+)\)$', expr)
        if m:
            v = self._evaluate_expression(m[1])
            if isinstance(v, (int, float)) and v > 0:
                return math.log10(v)
            self.error("log needs positive")
            return 0

        m = re.match(r'\$gcd\((.+),(.+)\)$', expr)
        if m:
            a = int(self._evaluate_expression(m[1].strip()))
            b = int(self._evaluate_expression(m[2].strip()))
            return math.gcd(a, b)

        m = re.match(r'\$lcm\((.+),(.+)\)$', expr)
        if m:
            a = int(self._evaluate_expression(m[1].strip()))
            b = int(self._evaluate_expression(m[2].strip()))
            return a * b // math.gcd(a, b)

        m = re.match(r'^(\w+)\.(\w+)\((.*)\)$', expr)
        if m:
            obj_name, method_name, args_str = m[1], m[2], m[3]
            if obj_name in self.variables:
                obj = self.variables[obj_name]
                args = self._parse_args(args_str) if args_str.strip() else []
                result = self._call_object_method(obj, method_name, args)
                if result is not None:
                    return result

        m = re.match(r'^(\w+)\((.*)\)$', expr)
        if m:
            fname = m[1]
            args = self._parse_args(m[2])
            if fname in self.function_handler.functions:
                return self.function_handler.call(fname, args, self)
            if fname in self.builtins:
                try:
                    return self.builtins[fname](*args)
                except:
                    self.error(f"call {fname} failed")
                    return None

        if expr.startswith('[') and expr.endswith(']'):
            content = expr[1:-1].strip()
            if ':' in content:
                return self._parse_dict(content)
            items = self._parse_args(content) if content else []
            return SoloArray(items)

        m = re.match(r'^(\w+)\.(\w+)$', expr)
        if m:
            obj_name, attr = m[1], m[2]
            if obj_name in self.variables:
                obj = self.variables[obj_name]
                if isinstance(obj, SoloArray):
                    if attr == 'length': return obj.length()
                    if attr == 'sum': return obj.sum()
                    if attr == 'avg': return obj.avg()
                    if attr == 'min': return obj.min()
                    if attr == 'max': return obj.max()
                elif isinstance(obj, SoloDict):
                    if attr == 'length': return obj.length()
                    if attr == 'keys': return obj.keys()
                    if attr == 'values': return obj.values()
                elif isinstance(obj, str):
                    if attr == 'length': return len(obj)
                    if attr == 'upper': return obj.upper()
                    if attr == 'lower': return obj.lower()
                elif isinstance(obj, SoloDate):
                    if attr == 'year': return obj.year()
                    if attr == 'month': return obj.month()
                    if attr == 'day': return obj.day()
            return None

        m = re.match(r'^(\w+)\[(\d+)\]$', expr)
        if m:
            name, idx = m[1], int(m[2])
            if name in self.variables and isinstance(self.variables[name], SoloArray):
                return self.variables[name].get(idx)
            return None

        if expr in self.variables:
            return self.variables[expr]

        for func in ['length', 'sum', 'avg', 'min', 'max']:
            m = re.match(rf'^{func}\((\w+)\)$', expr)
            if m:
                name = m[1]
                if name in self.variables and isinstance(self.variables[name], SoloArray):
                    return getattr(self.variables[name], func)()
                return 0 if func not in ('min', 'max') else None

        try:
            if '.' in expr:
                return float(expr)
            return int(expr)
        except:
            pass

        m = re.match(r'sqrt\((.+)\)$', expr)
        if m:
            v = self._evaluate_expression(m[1])
            if self._is_number(v):
                return math.sqrt(v)
            self.error("sqrt error")
            return 0

        m = re.match(r'root\((.+),(.+)\)$', expr)
        if m:
            v = self._evaluate_expression(m[1])
            n = self._evaluate_expression(m[2])
            if self._is_number(v) and self._is_number(n):
                return v ** (1 / n)
            self.error("root error")
            return 0

        for op in ['<=', '>=', '!=', '==', '<', '>']:
            if op in expr:
                left, right = expr.split(op, 1)
                lv = self._evaluate_expression(left.strip())
                rv = self._evaluate_expression(right.strip())
                if isinstance(lv, Percent): lv = lv.value
                if isinstance(rv, Percent): rv = rv.value
                lv = self._to_num(lv)
                rv = self._to_num(rv)
                if self._is_number(lv) and self._is_number(rv):
                    return eval(f'{lv} {op} {rv}')
                return eval(f'"{lv}" {op} "{rv}"')

        if '^' in expr and '"' not in expr:
            b, e = expr.rsplit('^', 1)
            bv = self._to_num(self._evaluate_expression(b.strip()))
            ev = self._to_num(self._evaluate_expression(e.strip()))
            return bv ** ev

        if ' mod ' in expr:
            parts = expr.split(' mod ', 1)
            lv = self._to_num(self._evaluate_expression(parts[0].strip()))
            rv = self._to_num(self._evaluate_expression(parts[1].strip()))
            if rv == 0:
                raise ZeroDivisionError("integer modulo by zero")
            return lv % rv

        for op in ('*', '/'):
            if op in expr:
                l, r = expr.split(op, 1)
                lv = self._evaluate_expression(l.strip())
                rv = self._evaluate_expression(r.strip())
                if isinstance(lv, Percent): lv = lv.value
                if isinstance(rv, Percent): rv = rv.value
                if op == '/' and rv == 0:
                    raise ZeroDivisionError("division by zero")
                if op == '*' and isinstance(lv, str) and isinstance(rv, int):
                    return lv * rv
                if op == '*' and isinstance(rv, str) and isinstance(lv, int):
                    return rv * lv
                if self._is_number(lv) and self._is_number(rv):
                    return lv * rv if op == '*' else lv / rv
                return str(lv) + str(rv)

        for op in ('+', '-'):
            if op in expr:
                l, r = expr.split(op, 1)
                lv = self._evaluate_expression(l.strip())
                rv = self._evaluate_expression(r.strip())
                if isinstance(lv, SoloDate) and isinstance(rv, SoloDate) and op == '-':
                    return lv - rv
                if isinstance(lv, Percent): lv = lv.value
                if isinstance(rv, Percent): rv = rv.value
                if isinstance(lv, str) or isinstance(rv, str):
                    return str(lv) + str(rv)
                if self._is_number(lv) and self._is_number(rv):
                    return lv + rv if op == '+' else lv - rv
                return str(lv) + str(rv)

        return expr

    def evaluate_expression(self, expr):
        return self._evaluate_expression(expr)

    def _call_object_method(self, obj, method_name, args):
        try:
            if isinstance(obj, SoloArray):
                if method_name == 'get': return obj.get(args[0]) if args else None
                if method_name == 'set': return obj.set(args[0], args[1]) if len(args) >= 2 else None
                if method_name == 'add': obj.add(args[0]) if args else None; return obj
                if method_name == 'remove': return obj.remove(args[0]) if args else None
                if method_name == 'length': return obj.length()
                if method_name == 'sum': return obj.sum()
                if method_name == 'avg': return obj.avg()
                if method_name == 'min': return obj.min()
                if method_name == 'max': return obj.max()
            elif isinstance(obj, SoloDict):
                if method_name == 'value': return obj.value(args[0]) if args else None
                if method_name == 'key': return obj.key(args[0]) if args else None
                if method_name == 'add': 
                    if len(args) >= 2:
                        obj.add(args[0], args[1])
                        return obj
                    return None
                if method_name == 'remove': return obj.remove(args[0]) if args else None
                if method_name == 'has': return obj.has(args[0]) if args else None
                if method_name == 'keys': return obj.keys()
                if method_name == 'values': return obj.values()
                if method_name == 'length': return obj.length()
            elif isinstance(obj, str):
                if method_name == 'length': return len(obj)
                if method_name == 'upper': return obj.upper()
                if method_name == 'lower': return obj.lower()
            elif isinstance(obj, SoloDate):
                if method_name == 'year': return obj.year()
                if method_name == 'month': return obj.month()
                if method_name == 'day': return obj.day()
        except:
            pass
        return None

    def _parse_args(self, s):
        if not s.strip():
            return []
        args = []
        cur = ""
        in_q = False
        quote_char = None
        depth = 0
        for ch in s:
            if ch in '"\'':
                if not in_q:
                    in_q = True
                    quote_char = ch
                    cur += ch
                elif ch == quote_char:
                    in_q = False
                    quote_char = None
                    cur += ch
                else:
                    cur += ch
            elif ch in '([{' and not in_q:
                depth += 1
                cur += ch
            elif ch in ')]}' and not in_q:
                depth -= 1
                cur += ch
            elif ch == ',' and depth == 0 and not in_q:
                args.append(self._evaluate_expression(cur.strip()))
                cur = ""
            else:
                cur += ch
        if cur.strip():
            args.append(self._evaluate_expression(cur.strip()))
        return args

    def _parse_dict(self, content):
        pairs = []
        if content.strip():
            for pair in self._split_semicolon(content):
                if ':' in pair:
                    k, v = pair.split(':', 1)
                    key = k.strip().strip('"').strip("'")
                    val = self._evaluate_expression(v.strip())
                    pairs.append((key, val))
        return SoloDict(pairs)

    def _split_semicolon(self, text):
        parts = []
        cur = ""
        in_q = False
        quote_char = None
        for ch in text:
            if ch in '"\'':
                if not in_q:
                    in_q = True
                    quote_char = ch
                    cur += ch
                elif ch == quote_char:
                    in_q = False
                    quote_char = None
                    cur += ch
                else:
                    cur += ch
            elif ch == ';' and not in_q:
                parts.append(cur.strip())
                cur = ""
            else:
                cur += ch
        if cur.strip():
            parts.append(cur.strip())
        return parts

    def find_matching_brace(self, lines, start):
        d = 0
        for i in range(start, len(lines)):
            d += lines[i].count('{') - lines[i].count('}')
            if d == 0:
                return i
        return len(lines) - 1

    def find_else_for_when(self, lines, when_start):
        depth = 1
        for i in range(when_start + 1, len(lines)):
            line = lines[i].strip()
            depth += line.count('{') - line.count('}')
            if depth == 1 and 'else' in line:
                return i
            if depth == 0:
                if 'else' in line:
                    return i
                if i + 1 < len(lines):
                    next_line = lines[i + 1].strip()
                    if next_line.startswith('else'):
                        return i + 1
                return None
        return None

    def find_matching_function_end(self, lines, start):
        for i in range(start + 1, len(lines)):
            if '}f' in lines[i]:
                return i
        return len(lines) - 1

    def _execute_block(self, lines, start, end):
        i = start
        while i <= end:
            line = lines[i].strip()
            line = self.translate(line)
            if not line or line in ('{', '}') or '} else' in line or line == 'else' or line.startswith('else {') or line == '}f':
                i += 1
                continue
            try:
                if line.startswith('when '):
                    i = self._execute_when(lines, i)
                elif line.startswith('loop '):
                    i = self._execute_loop(lines, i)
                elif line.startswith('for '):
                    i = self._execute_for_loop(lines, i)
                elif line.startswith('function '):
                    i = self._execute_function_def(lines, i)
                elif line.startswith('try '):
                    i = self._execute_try(lines, i)
                else:
                    self._execute_line(line)
                    i += 1
            except ReturnException:
                raise
        return None

    def _execute_when(self, lines, idx):
        line = lines[idx].strip()
        if '{' in line:
            cond = line[5:line.index('{')].strip()
        else:
            cond = line[5:].strip()
        body_start = idx
        if '{' not in line:
            body_start = idx + 1
        body_end = self.find_matching_brace(lines, body_start)
        else_idx = self.find_else_for_when(lines, idx)

        if self._evaluate_expression(cond):
            try:
                if '{' in line:
                    self._execute_block(lines, idx + 1, body_end - 1)
                else:
                    self._execute_block(lines, idx + 2, body_end - 1)
            except ReturnException:
                raise
            return body_end + 1
        elif else_idx:
            else_line = lines[else_idx].strip()
            try:
                if '{' in else_line:
                    else_block_start = else_idx + 1
                    else_block_end = self.find_matching_brace(lines, else_idx)
                    self._execute_block(lines, else_block_start, else_block_end - 1)
                    return else_block_end + 1
                else:
                    else_body_start = else_idx + 1
                    else_body_end = self.find_matching_brace(lines, else_body_start)
                    self._execute_block(lines, else_idx + 2, else_body_end - 1)
                    return else_body_end + 1
            except ReturnException:
                raise
        return body_end + 1

    def _execute_loop(self, lines, idx):
        line = lines[idx].strip()
        cond = line[5:line.index('{')].strip() if '{' in line else line[5:].strip()
        s, e = idx + 1, self.find_matching_brace(lines, idx)
        while self._evaluate_expression(cond):
            try:
                self._execute_block(lines, s, e - 1)
            except ReturnException:
                raise
        return e

    def _execute_for_loop(self, lines, idx):
        line = lines[idx].strip().replace('{', '').strip()
        m = re.match(r'for\s+(\w+)\s*~\s*(.+)', line)
        if not m:
            self.error("invalid for loop")
            return self.find_matching_brace(lines, idx)
        var, rng = m[1], m[2].strip()
        s, e = idx + 1, self.find_matching_brace(lines, idx)

        def run_loop(items):
            for item in items:
                self.set_variable(var, item)
                try:
                    self._execute_block(lines, s, e - 1)
                except ReturnException:
                    raise

        ftp = re.match(r'from\s+(.+)\s+to\s+(.+)\s+step\s+(.+)', rng)
        if ftp:
            st = int(self._evaluate_expression(ftp[1]))
            en = int(self._evaluate_expression(ftp[2]))
            step = int(self._evaluate_expression(ftp[3]))
            rng_range = range(st, en + 1, step) if step > 0 else range(st, en - 1, step)
            run_loop(rng_range)
            return e

        ft = re.match(r'from\s+(.+)\s+to\s+(.+)', rng)
        if ft:
            st = int(self._evaluate_expression(ft[1]))
            en = int(self._evaluate_expression(ft[2]))
            step = 1 if st <= en else -1
            rng_range = range(st, en + 1) if step > 0 else range(st, en - 1, -1)
            run_loop(rng_range)
            return e

        ia = re.match(r'in\s+(.+)', rng)
        if ia:
            arrn = ia[1].strip()
            if arrn in self.variables:
                container = self.variables[arrn]
                if isinstance(container, SoloArray):
                    items = container.items
                elif isinstance(container, SoloDict):
                    items = list(container.data.keys())
                elif isinstance(container, str):
                    items = list(container)
                else:
                    items = []
                run_loop(items)
            return e

        self.error("invalid for range")
        return e

    def _execute_function_def(self, lines, idx):
        line = lines[idx].strip()
        m = re.match(r'function\s+(\w+)\s*\((.*)\)\s*f{', line)
        if not m:
            self.error("invalid function def")
            return self.find_matching_brace(lines, idx)
        name = m[1]
        params_str = m[2].strip()
        params, defaults = [], {}
        if params_str:
            for p in params_str.split(','):
                p = p.strip()
                if '=' in p:
                    n, v = p.split('=', 1)
                    params.append(n.strip())
                    defaults[n.strip()] = self._evaluate_expression(v.strip())
                else:
                    params.append(p)
        block_end = self.find_matching_function_end(lines, idx)
        body = '\n'.join(lines[idx + 1:block_end])
        self.function_handler.define(name, params, body, defaults)
        return block_end + 1

    def _execute_try(self, lines, idx):
        try_end = self.find_matching_brace(lines, idx)
        try_lines = lines[idx + 1:try_end]
        error_occurred = False
        try:
            self._execute_block(try_lines, 0, len(try_lines) - 1)
        except ReturnException:
            raise
        except Exception:
            error_occurred = True

        i = try_end + 1
        while i < len(lines):
            l = lines[i].strip()
            if l.startswith('error'):
                if error_occurred:
                    if '{' in l:
                        s = i + 1
                        e = self.find_matching_brace(lines, i)
                        self._execute_block(lines, s, e - 1)
                    elif i + 1 < len(lines) and '{' in lines[i + 1]:
                        s = i + 2
                        e = self.find_matching_brace(lines, i + 1)
                        self._execute_block(lines, s, e - 1)
                i = self._skip_block(lines, i)
            elif l.startswith('always'):
                if '{' in l:
                    s = i + 1
                    e = self.find_matching_brace(lines, i)
                    self._execute_block(lines, s, e - 1)
                elif i + 1 < len(lines) and '{' in lines[i + 1]:
                    s = i + 2
                    e = self.find_matching_brace(lines, i + 1)
                    self._execute_block(lines, s, e - 1)
                i = self._skip_block(lines, i)
            else:
                break
            i += 1
        return i

    def _skip_block(self, lines, i):
        if '{' in lines[i]:
            return self.find_matching_brace(lines, i)
        elif i + 1 < len(lines) and '{' in lines[i + 1]:
            return self.find_matching_brace(lines, i + 1)
        return i

    def _execute_line(self, line):
        line = self.translate(line)
        if '...' in line:
            line = line[:line.index('...')].strip()
        if not line:
            return None
        if line.startswith('write '):
            content = line[6:].strip()
            cm = re.match(r'(red|green|yellow|blue|purple|cyan|white)\((.+)\)$', content)
            if cm:
                color, inner = cm[1], cm[2].strip()
                result = self._evaluate_write_content(inner)
                print(self.color_text(result, color))
            else:
                result = self._evaluate_write_content(content)
                print(result)
            return None
        if line.startswith('set '):
            m = re.match(r'set\s+(\w+)\s*=\s*(.+)', line)
            if m:
                vn, vs = m[1], m[2].strip()
                if vs.startswith('input'):
                    pm = re.search(r'input\s*\(\s*"([^"]*)"\s*\)', vs)
                    prompt = pm[1] if pm else ""
                    val = smart_convert(input(prompt))
                else:
                    val = self._evaluate_expression(vs)
                self.set_variable(vn, val)
            return None
        if line.startswith('add_to '):
            m = re.match(r'add_to\s+(\w+)\s+(.+)', line)
            if m:
                n, v = m[1], m[2].strip()
                if n in self.variables and isinstance(self.variables[n], SoloArray):
                    self.variables[n].add(self._evaluate_expression(v))
            return None
        if line.startswith('remove_from '):
            m = re.match(r'remove_from\s+(\w+)\s+(\d+)', line)
            if m:
                n, idx = m[1], int(m[2])
                if n in self.variables and isinstance(self.variables[n], SoloArray):
                    self.variables[n].remove(idx)
            return None
        if '=' in line:
            m = re.match(r'(\w+)\s*=\s*(.+)', line)
            if m:
                vn, vs = m[1], m[2].strip()
                if vn in self.variables:
                    if vs.startswith('input'):
                        pm = re.search(r'input\s*\(\s*"([^"]*)"\s*\)', vs)
                        prompt = pm[1] if pm else ""
                        self.set_variable(vn, smart_convert(input(prompt)))
                    else:
                        self.set_variable(vn, self._evaluate_expression(vs))
                else:
                    self.error(f"undefined variable '{vn}'")
            return None
        if line in self.variables:
            print(self._format_val(self.variables[line]))
            return None
        if line == 'break':
            return None
        if line == 'continue':
            return None
        if line == 'return':
            raise ReturnException(None)
        if line.startswith('return '):
            raise ReturnException(self._evaluate_expression(line[7:].strip()))
        res = self._evaluate_expression(line)
        if res is not None and res != line:
            print(self._format_val(res))
        return None

    def execute_code(self, code_str):
        lines = [l.rstrip() for l in code_str.split('\n')]
        i = 0
        while i < len(lines):
            line = lines[i].strip()
            if not line or line in ('{', '}') or line.startswith('} else') or line == 'else' or line.startswith('else {') or line == '}f':
                i += 1
                continue
            if line.startswith('when '):
                i = self._execute_when(lines, i)
            elif line.startswith('loop '):
                i = self._execute_loop(lines, i)
            elif line.startswith('for '):
                i = self._execute_for_loop(lines, i)
            elif line.startswith('function '):
                i = self._execute_function_def(lines, i)
            elif line.startswith('try '):
                i = self._execute_try(lines, i)
            else:
                try:
                    self._execute_line(line)
                except ReturnException:
                    pass
                i += 1

    def RUN(self, filename):
        if not filename.lower().endswith(".hp"):
            self.error("Only .hp files are supported!")
            return False
   
        try:
            with open(filename, 'r', encoding='utf-8') as f:
                content = f.read()
            print(f"HP v1.0.0 - Running {filename}\n{'—' * 30}")
            self.execute_code(content)
            print(f"{'—' * 30}\nExecution finished.")
            return True
        except FileNotFoundError:
            self.error(f"file '{filename}' not found")
            return False
        except Exception as e:
            self.error(str(e))
            import traceback
            traceback.print_exc()
            return False

if __name__ == "__main__":
    ss = HP()
    if len(sys.argv) > 1:
        ss.RUN(sys.argv[1])
    else:
        fn = input("FileName: ")
        os.system("clear" if os.name != 'nt' else "cls")
        ss.RUN(fn)
