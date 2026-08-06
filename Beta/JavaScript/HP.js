#!/usr/bin/env node
const fs = require('fs');
const readlineSync = require('readline-sync');

// ---------- تبدیل تاریخ شمسی / میلادی (بدون وابستگی خارجی) ----------
function gregorianToJalali(gy, gm, gd) {
  const g_d_m = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334];
  let gy2 = (gm > 2) ? (gy + 1) : gy;
  let days = 355666 + (365 * gy) + Math.floor((gy2 + 3) / 4) - Math.floor((gy2 + 99) / 100) + Math.floor((gy2 + 399) / 400) + gd + g_d_m[gm - 1];
  let jy = -1595 + (33 * Math.floor(days / 12053));
  days %= 12053;
  jy += 4 * Math.floor(days / 1461);
  days %= 1461;
  if (days > 365) {
    jy += Math.floor((days - 1) / 365);
    days = (days - 1) % 365;
  }
  let jm, jd;
  if (days < 186) {
    jm = 1 + Math.floor(days / 31);
    jd = 1 + (days % 31);
  } else {
    jm = 7 + Math.floor((days - 186) / 30);
    jd = 1 + ((days - 186) % 30);
  }
  return [jy, jm, jd];
}

function jalaliToGregorian(jy, jm, jd) {
  jy += 1595;
  let days = -355668 + (365 * jy) + (Math.floor(jy / 33) * 8) + Math.floor(((jy % 33) + 3) / 4);
  if (jm < 7) days += (jm - 1) * 31;
  else days += ((jm - 7) * 30) + 186;
  days += jd - 1;
  let gy = 400 * Math.floor(days / 146097);
  days %= 146097;
  if (days > 36524) {
    gy += 100 * Math.floor(--days / 36524);
    days %= 36524;
    if (days >= 365) days++;
  }
  gy += 4 * Math.floor(days / 1461);
  days %= 1461;
  if (days > 365) {
    gy += Math.floor((days - 1) / 365);
    days = (days - 1) % 365;
  }
  let gd = days + 1;
  let sal_a = [0, 31, ((gy % 4 === 0 && gy % 100 !== 0) || (gy % 400 === 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
  let gm = 1;
  while (gm <= 12 && gd > sal_a[gm]) {
    gd -= sal_a[gm];
    gm++;
  }
  return [gy, gm, gd];
}

// ---------- کلاس‌های کمکی ----------
class ReturnException extends Error {
  constructor(value) {
    super('return');
    this.value = value;
  }
}

class Percent {
  constructor(value) {
    this.value = value / 100.0;
  }
  apply(number) {
    return number * this.value;
  }
  toString() {
    return `${this.value * 100}%`;
  }
}

class SoloDate {
  constructor(year, month, day, isJalali = true) {
    this.isJalali = isJalali;
    if (isJalali) {
      this.jalaliYear = year;
      this.jalaliMonth = month;
      this.jalaliDay = day;
      const [gy, gm, gd] = jalaliToGregorian(year, month, day);
      this.gy = gy;
      this.gm = gm;
      this.gd = gd;
    } else {
      this.gy = year;
      this.gm = month;
      this.gd = day;
      const [jy, jm, jd] = gregorianToJalali(year, month, day);
      this.jalaliYear = jy;
      this.jalaliMonth = jm;
      this.jalaliDay = jd;
    }
  }

  toJalaliString() {
    const y = this.jalaliYear.toString();
    const m = this.jalaliMonth.toString().padStart(2, '0');
    const d = this.jalaliDay.toString().padStart(2, '0');
    return `${y}/${m}/${d}`;
  }

  toGregorianString() {
    const y = this.gy.toString();
    const m = this.gm.toString().padStart(2, '0');
    const d = this.gd.toString().padStart(2, '0');
    return `${y}/${m}/${d}`;
  }

  diff(other) {
    // اختلاف روز (میلادی)
    const d1 = new Date(this.gy, this.gm - 1, this.gd);
    const d2 = new Date(other.gy, other.gm - 1, other.gd);
    return (d1 - d2) / (1000 * 60 * 60 * 24);
  }

  year() { return this.isJalali ? this.jalaliYear : this.gy; }
  month() { return this.isJalali ? this.jalaliMonth : this.gm; }
  day() { return this.isJalali ? this.jalaliDay : this.gd; }

  static today() {
    const now = new Date();
    const [jy, jm, jd] = gregorianToJalali(now.getFullYear(), now.getMonth() + 1, now.getDate());
    const sd = new SoloDate(jy, jm, jd, true);
    // اطمینان از تاریخ میلادی درست
    sd.gy = now.getFullYear();
    sd.gm = now.getMonth() + 1;
    sd.gd = now.getDate();
    return sd;
  }

  toString() { return this.toJalaliString(); }
}

class SoloArray {
  constructor(items = []) {
    this.items = Array.isArray(items) ? [...items] : [];
  }

  get(index) { return (index >= 1 && index <= this.items.length) ? this.items[index - 1] : null; }
  set(index, value) {
    if (index >= 1 && index <= this.items.length) { this.items[index - 1] = value; return true; }
    return false;
  }
  add(value) { this.items.push(value); return this; }
  remove(index) {
    if (index >= 1 && index <= this.items.length) { this.items.splice(index - 1, 1); return true; }
    return false;
  }
  length() { return this.items.length; }
  sum() { return this.items.filter(v => typeof v === 'number').reduce((a, b) => a + b, 0); }
  avg() {
    const nums = this.items.filter(v => typeof v === 'number');
    return nums.length ? this.sum() / nums.length : 0;
  }
  min() {
    const nums = this.items.filter(v => typeof v === 'number');
    return nums.length ? Math.min(...nums) : null;
  }
  max() {
    const nums = this.items.filter(v => typeof v === 'number');
    return nums.length ? Math.max(...nums) : null;
  }
  toString() { return `[${this.items.map(i => i === null ? 'null' : i.toString()).join(', ')}]`; }
  [Symbol.iterator]() { return this.items[Symbol.iterator](); }
}

class SoloDict {
  constructor(pairs = []) {
    this.data = {};
    if (pairs) {
      for (const [k, v] of pairs) {
        this.data[k] = v;
      }
    }
  }
  value(key) { return this.data.hasOwnProperty(key) ? this.data[key] : null; }
  key(val) {
    for (const [k, v] of Object.entries(this.data)) {
      if (v === val) return k;
    }
    return null;
  }
  add(key, value) { this.data[key] = value; return this; }
  remove(key) {
    if (key in this.data) { delete this.data[key]; return true; }
    return false;
  }
  has(key) { return key in this.data; }
  keys() { return new SoloArray(Object.keys(this.data)); }
  values() { return new SoloArray(Object.values(this.data)); }
  length() { return Object.keys(this.data).length; }
  toString() {
    const items = Object.entries(this.data).map(([k, v]) => {
      const keyStr = typeof k === 'string' ? `"${k}"` : String(k);
      return `${keyStr}:${v}`;
    });
    return `[${items.join('; ')}]`;
  }
}

function smartConvert(value) {
  if (typeof value !== 'string') return value;
  value = value.trim();
  if (value.toLowerCase() === 'null' || value === '') return null;
  if (value.toLowerCase() === 'true') return true;
  if (value.toLowerCase() === 'false') return false;
  if (value.endsWith('%')) {
    const num = parseFloat(value.slice(0, -1));
    if (!isNaN(num)) return new Percent(num);
    return value;
  }
  if (/^-?\d+$/.test(value)) return parseInt(value, 10);
  if (/^-?\d+\.\d+$/.test(value)) return parseFloat(value);
  return value;
}

class FunctionHandler {
  constructor() {
    this.keywords = {
      "chap": "write",
      "set": "set",
      "agar": "when",
      "vagarna": "else",
      "loop": "loop",
      "baraye": "for",
      "az": "from",
      "ta": "to",
      "gam": "step",
      "dar": "in",
      "tabe": "function",
      "bargard": "return",
      "emtehan": "try",
      "khata": "error",
      "hamishe": "always",
      "ezafeBe": "add_to",
      "hazfAz": "remove_from",
      "shekan": "break",
      "edame": "continue",
      "begir": "input",
      "baghimande": "mod",
      "dorost": "true",
      "ghalat": "false",
      "hich": "null"
    };
    this.functions = {};
  }

  define(name, params, bodyLines, defaultValues = {}) {
    this.functions[name] = { params, body: bodyLines, defaults: defaultValues };
  }

  call(name, args, executor) {
    if (!(name in this.functions)) return null;
    const func = this.functions[name];
    const { params, defaults, body } = func;

    const oldValues = {};
    for (const param of params) {
      oldValues[param] = (param in executor.variables) ? executor.variables[param] : null;
    }

    for (let i = 0; i < params.length; i++) {
      const param = params[i];
      if (i < args.length) {
        executor.setVariable(param, args[i]);
      } else if (param in defaults) {
        executor.setVariable(param, defaults[param]);
      } else {
        executor.setVariable(param, null);
      }
    }

    let returnValue = null;
    const lines = body.split('\n');
    try {
      executor._executeBlock(lines, 0, lines.length - 1);
    } catch (e) {
      if (e instanceof ReturnException) {
        returnValue = e.value;
      } else {
        executor.error(`Error in function '${name}': ${e.message}`);
      }
    }

    // restore variables
    for (const param of params) {
      if (oldValues[param] !== null) {
        executor.variables[param] = oldValues[param];
      } else {
        delete executor.variables[param];
      }
    }
    return returnValue;
  }
}

class HP {
  constructor() {
    this.variables = {};
    this.colors = {
      red: '\x1b[91m',
      green: '\x1b[92m',
      yellow: '\x1b[93m',
      blue: '\x1b[94m',
      purple: '\x1b[95m',
      cyan: '\x1b[96m',
      white: '\x1b[97m',
      reset: '\x1b[0m'
    };
    this.functionHandler = new FunctionHandler();
    this.builtins = {
      sqrt: x => Math.sqrt(Number(x)),
      int: x => Math.trunc(Number(x)),
      float: x => parseFloat(x),
      str: x => String(x),
      bool: x => Boolean(x),
      abs: x => this._isNumber(x) ? Math.abs(Number(x)) : 0
    };
  }

  translate(line) {
    for (const [hp, old] of Object.entries(this.functionHandler.keywords)) {
      const regex = new RegExp(`\\b${hp}\\b`, 'gi');
      if (regex.test(line)) {
        return line.replace(regex, old);
      }
    }
    return line;
  }

  setVariable(name, value) { this.variables[name] = value; }
  error(msg) { console.log(`${this.colors.red}Error: ${msg}${this.colors.reset}`); }
  colorText(text, color) { return `${this.colors[color] || ''}${text}${this.colors.reset}`; }
  _isNumber(v) { return typeof v === 'number' && isFinite(v); }
  _toNum(v) {
    if (typeof v === 'number') return v;
    if (typeof v === 'boolean') return v ? 1 : 0;
    if (v instanceof Percent) return v.value;
    if (typeof v === 'string') {
      const n = Number(v);
      return isNaN(n) ? v : n;
    }
    return v;
  }
  _formatVal(val) {
    if (val === null) return 'null';
    if (typeof val === 'boolean') return val ? 'true' : 'false';
    if (val instanceof SoloDate) return val.toJalaliString();
    if (val instanceof Percent) return val.toString();
    if (val instanceof SoloArray || val instanceof SoloDict) return val.toString();
    return val;
  }

  _evaluateWriteContent(content) {
    if (!content) return '';
    const val = this._evaluateExpression(content);
    return String(this._formatVal(val));
  }

  _evaluateExpression(expr) {
    expr = String(expr).trim();
    if (!expr) return '';
    if ((expr.startsWith('"') && expr.endsWith('"')) || (expr.startsWith("'") && expr.endsWith("'"))) {
      return expr.slice(1, -1);
    }
    if (expr.toLowerCase() === 'null') return null;
    if (expr.toLowerCase() === 'true') return true;
    if (expr.toLowerCase() === 'false') return false;

    // پرانتزهای بیرونی
    if (expr.startsWith('(')) {
      let depth = 0;
      let closeIdx = -1;
      for (let i = 0; i < expr.length; i++) {
        if (expr[i] === '(') depth++;
        else if (expr[i] === ')') depth--;
        if (depth === 0) { closeIdx = i; break; }
      }
      if (closeIdx === expr.length - 1) {
        return this._evaluateExpression(expr.slice(1, -1));
      }
    }

    // درصد
    if (expr.endsWith('%') && !expr.startsWith('$')) {
      const p = parseFloat(expr.slice(0, -1));
      if (!isNaN(p)) return new Percent(p);
    }

    // تاریخ
    if (expr === '@today') return SoloDate.today();
    let m = expr.match(/^@(\d{4})\/(\d{2})\/(\d{2})$/);
    if (m) return new SoloDate(parseInt(m[1]), parseInt(m[2]), parseInt(m[3]), true);
    m = expr.match(/^@@(\d{4})\/(\d{2})\/(\d{2})$/);
    if (m) return new SoloDate(parseInt(m[1]), parseInt(m[2]), parseInt(m[3]), false);

    // فاکتوریل
    if (expr.endsWith('!') && !expr.startsWith('!!')) {
      const v = this._evaluateExpression(expr.slice(0, -1));
      const num = parseInt(v);
      if (num < 0) { this.error("Factorial of negative is undefined"); return 0; }
      let fact = 1;
      for (let i = 2; i <= num; i++) fact *= i;
      return fact;
    }

    // قدرمطلق
    if (expr.startsWith('|') && expr.endsWith('|')) {
      const v = this._evaluateExpression(expr.slice(1, -1));
      if (typeof v === 'number') return Math.abs(v);
      this.error("abs error");
      return 0;
    }

    // توابع مثلثاتی
    for (const func of ['sin', 'cos', 'tan']) {
      m = expr.match(new RegExp(`\\$${func}\\((.+)\\)`));
      if (m) {
        const v = this._evaluateExpression(m[1]);
        if (typeof v === 'number') return Math[func](v * Math.PI / 180);
        this.error(`${func} needs number`);
        return 0;
      }
    }

    m = expr.match(/^\$log\((.+)\)$/);
    if (m) {
      const v = this._evaluateExpression(m[1]);
      if (typeof v === 'number' && v > 0) return Math.log10(v);
      this.error("log needs positive");
      return 0;
    }

    m = expr.match(/^\$gcd\((.+),(.+)\)$/);
    if (m) {
      const a = parseInt(this._evaluateExpression(m[1].trim()));
      const b = parseInt(this._evaluateExpression(m[2].trim()));
      const gcd = (x, y) => (!y ? x : gcd(y, x % y));
      return gcd(Math.abs(a), Math.abs(b));
    }

    m = expr.match(/^\$lcm\((.+),(.+)\)$/);
    if (m) {
      const a = parseInt(this._evaluateExpression(m[1].trim()));
      const b = parseInt(this._evaluateExpression(m[2].trim()));
      const gcd = (x, y) => (!y ? x : gcd(y, x % y));
      const g = gcd(Math.abs(a), Math.abs(b));
      return (a * b) / g;
    }

    // متدهای شیء
    m = expr.match(/^(\w+)\.(\w+)\((.*)\)$/);
    if (m) {
      const objName = m[1], methodName = m[2], argsStr = m[3];
      if (objName in this.variables) {
        const obj = this.variables[objName];
        const args = argsStr.trim() ? this._parseArgs(argsStr) : [];
        const result = this._callObjectMethod(obj, methodName, args);
        if (result !== undefined) return result;
      }
    }

    // فراخوانی توابع
    m = expr.match(/^(\w+)\((.*)\)$/);
    if (m) {
      const fname = m[1];
      const args = this._parseArgs(m[2]);
      if (fname in this.functionHandler.functions) {
        return this.functionHandler.call(fname, args, this);
      }
      if (fname in this.builtins) {
        try {
          return this.builtins[fname](...args);
        } catch (e) {
          this.error(`call ${fname} failed`);
          return null;
        }
      }
    }

    // آرایه و دیکشنری
    if (expr.startsWith('[') && expr.endsWith(']')) {
      const content = expr.slice(1, -1).trim();
      if (content.includes(':')) return this._parseDict(content);
      const items = content ? this._parseArgs(content) : [];
      return new SoloArray(items);
    }

    // ویژگی‌های آبجکت
    m = expr.match(/^(\w+)\.(\w+)$/);
    if (m) {
      const objName = m[1], attr = m[2];
      if (objName in this.variables) {
        const obj = this.variables[objName];
        if (obj instanceof SoloArray) {
          if (attr === 'length') return obj.length();
          if (attr === 'sum') return obj.sum();
          if (attr === 'avg') return obj.avg();
          if (attr === 'min') return obj.min();
          if (attr === 'max') return obj.max();
        } else if (obj instanceof SoloDict) {
          if (attr === 'length') return obj.length();
          if (attr === 'keys') return obj.keys();
          if (attr === 'values') return obj.values();
        } else if (typeof obj === 'string') {
          if (attr === 'length') return obj.length;
          if (attr === 'upper') return obj.toUpperCase();
          if (attr === 'lower') return obj.toLowerCase();
        } else if (obj instanceof SoloDate) {
          if (attr === 'year') return obj.year();
          if (attr === 'month') return obj.month();
          if (attr === 'day') return obj.day();
        }
      }
      return null;
    }

    // دسترسی با ایندکس
    m = expr.match(/^(\w+)\[(\d+)\]$/);
    if (m) {
      const name = m[1], idx = parseInt(m[2]);
      if (name in this.variables && this.variables[name] instanceof SoloArray) {
        return this.variables[name].get(idx);
      }
      return null;
    }

    // متغیر ساده
    if (expr in this.variables) return this.variables[expr];

    // توابع تجمعی روی آرایه
    for (const func of ['length', 'sum', 'avg', 'min', 'max']) {
      m = expr.match(new RegExp(`^${func}\\((\\w+)\\)$`));
      if (m) {
        const name = m[1];
        if (name in this.variables && this.variables[name] instanceof SoloArray) {
          return this.variables[name][func]();
        }
        return func === 'min' || func === 'max' ? null : 0;
      }
    }

    // عدد
    if (/^-?\d+(\.\d+)?$/.test(expr)) return parseFloat(expr); // با int/float کاری نداره

    // sqrt قدیمی
    m = expr.match(/^sqrt\((.+)\)$/);
    if (m) {
      const v = this._evaluateExpression(m[1]);
      if (typeof v === 'number') return Math.sqrt(v);
      this.error("sqrt error");
      return 0;
    }
    m = expr.match(/^root\((.+),(.+)\)$/);
    if (m) {
      const v = this._evaluateExpression(m[1]);
      const n = this._evaluateExpression(m[2]);
      if (typeof v === 'number' && typeof n === 'number') return Math.pow(v, 1 / n);
      this.error("root error");
      return 0;
    }

    // عملگرهای مقایسه‌ای
    for (const op of ['<=', '>=', '!=', '==', '<', '>']) {
      if (expr.includes(op)) {
        const idx = expr.indexOf(op);
        const left = expr.substring(0, idx).trim();
        const right = expr.substring(idx + op.length).trim();
        let lv = this._evaluateExpression(left);
        let rv = this._evaluateExpression(right);
        if (lv instanceof Percent) lv = lv.value;
        if (rv instanceof Percent) rv = rv.value;
        lv = this._toNum(lv);
        rv = this._toNum(rv);
        if (this._isNumber(lv) && this._isNumber(rv)) {
          switch (op) {
            case '<': return lv < rv;
            case '>': return lv > rv;
            case '<=': return lv <= rv;
            case '>=': return lv >= rv;
            case '==': return lv == rv;
            case '!=': return lv != rv;
          }
        }
        return String(lv) === String(rv) ? (op === '==' ? true : op === '!=' ? false : undefined) : undefined;
      }
    }

    // توان
    if (expr.includes('^') && !expr.includes('"')) {
      const idx = expr.lastIndexOf('^');
      const b = this._toNum(this._evaluateExpression(expr.substring(0, idx).trim()));
      const e = this._toNum(this._evaluateExpression(expr.substring(idx + 1).trim()));
      return Math.pow(b, e);
    }

    // باقیمانده
    if (expr.includes(' mod ')) {
      const parts = expr.split(' mod ');
      const lv = this._toNum(this._evaluateExpression(parts[0].trim()));
      const rv = this._toNum(this._evaluateExpression(parts[1].trim()));
      if (rv === 0) throw new Error("integer modulo by zero");
      return lv % rv;
    }

    // ضرب و تقسیم
    for (const op of ['*', '/']) {
      if (expr.includes(op)) {
        const idx = expr.indexOf(op);
        const l = expr.substring(0, idx).trim();
        const r = expr.substring(idx + 1).trim();
        let lv = this._evaluateExpression(l);
        let rv = this._evaluateExpression(r);
        if (lv instanceof Percent) lv = lv.value;
        if (rv instanceof Percent) rv = rv.value;
        if (op === '/' && rv === 0) throw new Error("division by zero");
        if (op === '*' && typeof lv === 'string' && typeof rv === 'number') return lv.repeat(rv);
        if (op === '*' && typeof rv === 'string' && typeof lv === 'number') return rv.repeat(lv);
        if (this._isNumber(lv) && this._isNumber(rv)) return op === '*' ? lv * rv : lv / rv;
        return String(lv) + String(rv);
      }
    }

    // جمع و تفریق
    for (const op of ['+', '-']) {
      if (expr.includes(op)) {
        const idx = expr.indexOf(op);
        const l = expr.substring(0, idx).trim();
        const r = expr.substring(idx + 1).trim();
        let lv = this._evaluateExpression(l);
        let rv = this._evaluateExpression(r);
        if (lv instanceof SoloDate && rv instanceof SoloDate && op === '-') {
          return lv.diff(rv);
        }
        if (lv instanceof Percent) lv = lv.value;
        if (rv instanceof Percent) rv = rv.value;
        if (typeof lv === 'string' || typeof rv === 'string') return String(lv) + String(rv);
        if (this._isNumber(lv) && this._isNumber(rv)) return op === '+' ? lv + rv : lv - rv;
        return String(lv) + String(rv);
      }
    }

    return expr;
  }

  evaluateExpression(expr) { return this._evaluateExpression(expr); }

  _callObjectMethod(obj, methodName, args) {
    if (obj instanceof SoloArray) {
      switch (methodName) {
        case 'get': return args.length ? obj.get(args[0]) : null;
        case 'set': return args.length >= 2 ? obj.set(args[0], args[1]) : null;
        case 'add': if (args.length) obj.add(args[0]); return obj;
        case 'remove': return args.length ? obj.remove(args[0]) : null;
        case 'length': return obj.length();
        case 'sum': return obj.sum();
        case 'avg': return obj.avg();
        case 'min': return obj.min();
        case 'max': return obj.max();
      }
    } else if (obj instanceof SoloDict) {
      switch (methodName) {
        case 'value': return args.length ? obj.value(args[0]) : null;
        case 'key': return args.length ? obj.key(args[0]) : null;
        case 'add': if (args.length >= 2) obj.add(args[0], args[1]); return obj;
        case 'remove': return args.length ? obj.remove(args[0]) : null;
        case 'has': return args.length ? obj.has(args[0]) : null;
        case 'keys': return obj.keys();
        case 'values': return obj.values();
        case 'length': return obj.length();
      }
    } else if (typeof obj === 'string') {
      switch (methodName) {
        case 'length': return obj.length;
        case 'upper': return obj.toUpperCase();
        case 'lower': return obj.toLowerCase();
      }
    } else if (obj instanceof SoloDate) {
      switch (methodName) {
        case 'year': return obj.year();
        case 'month': return obj.month();
        case 'day': return obj.day();
      }
    }
    return null;
  }

  _parseArgs(s) {
    if (!s.trim()) return [];
    const args = [];
    let cur = '';
    let inQuote = false, quoteChar = null, depth = 0;
    for (const ch of s) {
      if (ch === '"' || ch === "'") {
        if (!inQuote) { inQuote = true; quoteChar = ch; cur += ch; }
        else if (ch === quoteChar) { inQuote = false; quoteChar = null; cur += ch; }
        else { cur += ch; }
      } else if ('([{'.includes(ch) && !inQuote) {
        depth++; cur += ch;
      } else if (')]}'.includes(ch) && !inQuote) {
        depth--; cur += ch;
      } else if (ch === ',' && depth === 0 && !inQuote) {
        args.push(this._evaluateExpression(cur.trim()));
        cur = '';
      } else {
        cur += ch;
      }
    }
    if (cur.trim()) args.push(this._evaluateExpression(cur.trim()));
    return args;
  }

  _parseDict(content) {
    const pairs = [];
    if (content.trim()) {
      for (const pair of this._splitSemicolon(content)) {
        if (pair.includes(':')) {
          const idx = pair.indexOf(':');
          const key = pair.substring(0, idx).trim().replace(/^"(.*)"$/, '$1').replace(/^'(.*)'$/, '$1');
          const val = this._evaluateExpression(pair.substring(idx + 1).trim());
          pairs.push([key, val]);
        }
      }
    }
    return new SoloDict(pairs);
  }

  _splitSemicolon(text) {
    const parts = [];
    let cur = '';
    let inQuote = false, quoteChar = null;
    for (const ch of text) {
      if (ch === '"' || ch === "'") {
        if (!inQuote) { inQuote = true; quoteChar = ch; cur += ch; }
        else if (ch === quoteChar) { inQuote = false; quoteChar = null; cur += ch; }
        else { cur += ch; }
      } else if (ch === ';' && !inQuote) {
        parts.push(cur.trim());
        cur = '';
      } else {
        cur += ch;
      }
    }
    if (cur.trim()) parts.push(cur.trim());
    return parts;
  }

  findMatchingBrace(lines, start) {
    let depth = 0;
    for (let i = start; i < lines.length; i++) {
      const open = (lines[i].match(/{/g) || []).length;
      const close = (lines[i].match(/}/g) || []).length;
      depth += open - close;
      if (depth === 0) return i;
    }
    return lines.length - 1;
  }

  findElseForWhen(lines, whenStart) {
    let depth = 1;
    for (let i = whenStart + 1; i < lines.length; i++) {
      const line = lines[i].trim();
      const open = (line.match(/{/g) || []).length;
      const close = (line.match(/}/g) || []).length;
      depth += open - close;
      if (depth === 1 && line.includes('else')) return i;
      if (depth === 0) {
        if (line.includes('else')) return i;
        if (i + 1 < lines.length) {
          const nextLine = lines[i + 1].trim();
          if (nextLine.startsWith('else')) return i + 1;
        }
        return null;
      }
    }
    return null;
  }

  findMatchingFunctionEnd(lines, start) {
    for (let i = start + 1; i < lines.length; i++) {
      if (lines[i].includes('}f')) return i;
    }
    return lines.length - 1;
  }

  _executeBlock(lines, start, end) {
    let i = start;
    while (i <= end) {
      let line = lines[i].trim();
      line = this.translate(line);
      if (!line || line === '{' || line === '}' || line.includes('} else') || line === 'else' || line.startsWith('else {') || line === '}f') {
        i++; continue;
      }
      try {
        if (line.startsWith('when ')) i = this._executeWhen(lines, i);
        else if (line.startsWith('loop ')) i = this._executeLoop(lines, i);
        else if (line.startsWith('for ')) i = this._executeForLoop(lines, i);
        else if (line.startsWith('function ')) i = this._executeFunctionDef(lines, i);
        else if (line.startsWith('try ')) i = this._executeTry(lines, i);
        else { this._executeLine(line); i++; }
      } catch (e) {
        if (e instanceof ReturnException) throw e;
      }
    }
    return null;
  }

  _executeWhen(lines, idx) {
    let line = lines[idx].trim();
    let cond;
    if (line.includes('{')) cond = line.substring(5, line.indexOf('{')).trim();
    else cond = line.substring(5).trim();
    const bodyStart = idx;
    const bodyEnd = this.findMatchingBrace(lines, bodyStart);
    const elseIdx = this.findElseForWhen(lines, idx);

    if (this._evaluateExpression(cond)) {
      try {
        if (lines[idx].includes('{')) this._executeBlock(lines, idx + 1, bodyEnd - 1);
        else this._executeBlock(lines, idx + 2, bodyEnd - 1);
      } catch (e) { if (e instanceof ReturnException) throw e; }
      return bodyEnd + 1;
    } else if (elseIdx !== null) {
      const elseLine = lines[elseIdx].trim();
      try {
        if (elseLine.includes('{')) {
          const elseBlockStart = elseIdx + 1;
          const elseBlockEnd = this.findMatchingBrace(lines, elseIdx);
          this._executeBlock(lines, elseBlockStart, elseBlockEnd - 1);
          return elseBlockEnd + 1;
        } else {
          const elseBodyStart = elseIdx + 1;
          const elseBodyEnd = this.findMatchingBrace(lines, elseBodyStart);
          this._executeBlock(lines, elseIdx + 2, elseBodyEnd - 1);
          return elseBodyEnd + 1;
        }
      } catch (e) { if (e instanceof ReturnException) throw e; }
    }
    return bodyEnd + 1;
  }

  _executeLoop(lines, idx) {
    const line = lines[idx].trim();
    const cond = line.includes('{') ? line.substring(5, line.indexOf('{')).trim() : line.substring(5).trim();
    const s = idx + 1;
    const e = this.findMatchingBrace(lines, idx);
    while (this._evaluateExpression(cond)) {
      try { this._executeBlock(lines, s, e - 1); } catch (ex) { if (ex instanceof ReturnException) throw ex; }
    }
    return e;
  }

  _executeForLoop(lines, idx) {
    let line = lines[idx].trim().replace('{', '').trim();
    const m = line.match(/^for\s+(\w+)\s*~\s*(.+)/);
    if (!m) {
      this.error("invalid for loop");
      return this.findMatchingBrace(lines, idx);
    }
    const varName = m[1], rangePart = m[2].trim();
    const start = idx + 1, end = this.findMatchingBrace(lines, idx);

    const runLoop = (items) => {
      for (const item of items) {
        this.setVariable(varName, item);
        try { this._executeBlock(lines, start, end - 1); } catch (ex) { if (ex instanceof ReturnException) throw ex; }
      }
    };

    const ftp = rangePart.match(/^from\s+(.+)\s+to\s+(.+)\s+step\s+(.+)/);
    if (ftp) {
      const st = parseInt(this._evaluateExpression(ftp[1]));
      const en = parseInt(this._evaluateExpression(ftp[2]));
      const step = parseInt(this._evaluateExpression(ftp[3]));
      const range = [];
      if (step > 0) for (let i = st; i <= en; i += step) range.push(i);
      else for (let i = st; i >= en; i += step) range.push(i);
      runLoop(range);
      return end;
    }

    const ft = rangePart.match(/^from\s+(.+)\s+to\s+(.+)/);
    if (ft) {
      const st = parseInt(this._evaluateExpression(ft[1]));
      const en = parseInt(this._evaluateExpression(ft[2]));
      const step = st <= en ? 1 : -1;
      const range = [];
      if (step > 0) for (let i = st; i <= en; i++) range.push(i);
      else for (let i = st; i >= en; i--) range.push(i);
      runLoop(range);
      return end;
    }

    const ia = rangePart.match(/^in\s+(.+)/);
    if (ia) {
      const containerName = ia[1].trim();
      if (containerName in this.variables) {
        const container = this.variables[containerName];
        let items = [];
        if (container instanceof SoloArray) items = container.items;
        else if (container instanceof SoloDict) items = Object.keys(container.data);
        else if (typeof container === 'string') items = container.split('');
        runLoop(items);
      }
      return end;
    }

    this.error("invalid for range");
    return end;
  }

  _executeFunctionDef(lines, idx) {
    const line = lines[idx].trim();
    const m = line.match(/^function\s+(\w+)\s*\((.*)\)\s*f{/);
    if (!m) { this.error("invalid function def"); return this.findMatchingBrace(lines, idx); }
    const name = m[1];
    const paramsStr = m[2].trim();
    const params = [], defaults = {};
    if (paramsStr) {
      paramsStr.split(',').forEach(p => {
        p = p.trim();
        if (p.includes('=')) {
          const [n, v] = p.split('=').map(s => s.trim());
          params.push(n);
          defaults[n] = this._evaluateExpression(v);
        } else {
          params.push(p);
        }
      });
    }
    const blockEnd = this.findMatchingFunctionEnd(lines, idx);
    const body = lines.slice(idx + 1, blockEnd).join('\n');
    this.functionHandler.define(name, params, body, defaults);
    return blockEnd + 1;
  }

  _executeTry(lines, idx) {
    const tryEnd = this.findMatchingBrace(lines, idx);
    const tryLines = lines.slice(idx + 1, tryEnd);
    let errorOccurred = false;
    try {
      this._executeBlock(tryLines, 0, tryLines.length - 1);
    } catch (e) {
      if (e instanceof ReturnException) throw e;
      errorOccurred = true;
    }

    let i = tryEnd + 1;
    while (i < lines.length) {
      const l = lines[i].trim();
      if (l.startsWith('error')) {
        if (errorOccurred) {
          if (l.includes('{')) {
            const s = i + 1, e = this.findMatchingBrace(lines, i);
            this._executeBlock(lines, s, e - 1);
          } else if (i + 1 < lines.length && lines[i + 1].includes('{')) {
            const s = i + 2, e = this.findMatchingBrace(lines, i + 1);
            this._executeBlock(lines, s, e - 1);
          }
        }
        i = this._skipBlock(lines, i);
      } else if (l.startsWith('always')) {
        if (l.includes('{')) {
          const s = i + 1, e = this.findMatchingBrace(lines, i);
          this._executeBlock(lines, s, e - 1);
        } else if (i + 1 < lines.length && lines[i + 1].includes('{')) {
          const s = i + 2, e = this.findMatchingBrace(lines, i + 1);
          this._executeBlock(lines, s, e - 1);
        }
        i = this._skipBlock(lines, i);
      } else break;
      i++;
    }
    return i;
  }

  _skipBlock(lines, i) {
    if (lines[i].includes('{')) return this.findMatchingBrace(lines, i);
    if (i + 1 < lines.length && lines[i + 1].includes('{')) return this.findMatchingBrace(lines, i + 1);
    return i;
  }

  _executeLine(line) {
    line = this.translate(line);
    if (line.includes('...')) line = line.substring(0, line.indexOf('...')).trim();
    if (!line) return null;

    if (line.startsWith('write ')) {
      const content = line.substring(6).trim();
      const cm = content.match(/^(red|green|yellow|blue|purple|cyan|white)\((.+)\)$/);
      if (cm) {
        const color = cm[1], inner = cm[2].trim();
        const result = this._evaluateWriteContent(inner);
        console.log(this.colorText(result, color));
      } else {
        console.log(this._evaluateWriteContent(content));
      }
      return null;
    }

    if (line.startsWith('set ')) {
      const m = line.match(/^set\s+(\w+)\s*=\s*(.+)/);
      if (m) {
        const varName = m[1], valueExpr = m[2].trim();
        let val;
        if (valueExpr.startsWith('input')) {
          const pm = valueExpr.match(/input\s*\(\s*"([^"]*)"\s*\)/);
          const prompt = pm ? pm[1] : '';
          val = smartConvert(readlineSync.question(prompt));
        } else {
          val = this._evaluateExpression(valueExpr);
        }
        this.setVariable(varName, val);
      }
      return null;
    }

    if (line.startsWith('add_to ')) {
      const m = line.match(/^add_to\s+(\w+)\s+(.+)/);
      if (m) {
        const name = m[1], valExpr = m[2].trim();
        if (name in this.variables && this.variables[name] instanceof SoloArray) {
          this.variables[name].add(this._evaluateExpression(valExpr));
        }
      }
      return null;
    }

    if (line.startsWith('remove_from ')) {
      const m = line.match(/^remove_from\s+(\w+)\s+(\d+)/);
      if (m) {
        const name = m[1], idx = parseInt(m[2]);
        if (name in this.variables && this.variables[name] instanceof SoloArray) {
          this.variables[name].remove(idx);
        }
      }
      return null;
    }

    if (line.includes('=') && !line.startsWith('set ')) {
      const m = line.match(/^(\w+)\s*=\s*(.+)/);
      if (m) {
        const varName = m[1], expr = m[2].trim();
        if (varName in this.variables) {
          let val;
          if (expr.startsWith('input')) {
            const pm = expr.match(/input\s*\(\s*"([^"]*)"\s*\)/);
            const prompt = pm ? pm[1] : '';
            val = smartConvert(readlineSync.question(prompt));
          } else {
            val = this._evaluateExpression(expr);
          }
          this.setVariable(varName, val);
        } else {
          this.error(`undefined variable '${varName}'`);
        }
        return null;
      }
    }

    if (line in this.variables) {
      console.log(this._formatVal(this.variables[line]));
      return null;
    }

    if (line === 'return') throw new ReturnException(null);
    if (line.startsWith('return ')) throw new ReturnException(this._evaluateExpression(line.substring(7).trim()));

    const res = this._evaluateExpression(line);
    if (res !== null && res !== line) console.log(this._formatVal(res));
    return null;
  }

  executeCode(codeStr) {
    const lines = codeStr.split('\n').map(l => l.trimEnd());
    let i = 0;
    while (i < lines.length) {
      const line = lines[i].trim();
      if (!line || line === '{' || line === '}' || line.startsWith('} else') || line === 'else' || line.startsWith('else {') || line === '}f') {
        i++; continue;
      }
      if (line.startsWith('when ')) i = this._executeWhen(lines, i);
      else if (line.startsWith('loop ')) i = this._executeLoop(lines, i);
      else if (line.startsWith('for ')) i = this._executeForLoop(lines, i);
      else if (line.startsWith('function ')) i = this._executeFunctionDef(lines, i);
      else if (line.startsWith('try ')) i = this._executeTry(lines, i);
      else {
        try { this._executeLine(line); } catch (e) { if (e instanceof ReturnException) {/* از تابع برگشته */} }
        i++;
      }
    }
  }

  RUN(filename) {
    if (!filename.toLowerCase().endsWith('.hp')) {
      this.error("Only .hp files are supported!");
      return false;
    }
    try {
      const content = fs.readFileSync(filename, 'utf8');
      console.log(`HP v1.0.0 - Running ${filename}\n${'─'.repeat(30)}`);
      this.executeCode(content);
      console.log(`${'─'.repeat(30)}\nExecution finished.`);
      return true;
    } catch (e) {
      if (e.code === 'ENOENT') this.error(`file '${filename}' not found`);
      else { this.error(e.message); console.trace(e); }
      return false;
    }
  }
}

// ---------- اجرای برنامه ----------
if (require.main === module) {
  const hp = new HP();
  if (process.argv.length > 2) {
    hp.RUN(process.argv[2]);
  } else {
    const filename = readlineSync.question('FileName: ');
    console.clear();
    hp.RUN(filename);
  }
    }
