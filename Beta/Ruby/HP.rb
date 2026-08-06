#!/usr/bin/env ruby
# frozen_string_literal: true

require 'date'

# ---------- تبدیل تاریخ شمسی / میلادی (بدون کتابخونه خارجی) ----------
module Jalali
  def self.gregorian_to_jalali(gy, gm, gd)
    g_d_m = [0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334]
    gy2 = gm > 2 ? gy + 1 : gy
    days = 355666 + (365 * gy) + ((gy2 + 3) / 4).floor - ((gy2 + 99) / 100).floor + ((gy2 + 399) / 400).floor + gd + g_d_m[gm - 1]
    jy = -1595 + (33 * (days / 12053).floor)
    days %= 12053
    jy += 4 * (days / 1461).floor
    days %= 1461
    if days > 365
      jy += (days - 1) / 365
      days = (days - 1) % 365
    end
    if days < 186
      jm = 1 + (days / 31).floor
      jd = 1 + (days % 31)
    else
      jm = 7 + ((days - 186) / 30).floor
      jd = 1 + ((days - 186) % 30)
    end
    [jy, jm, jd]
  end

  def self.jalali_to_gregorian(jy, jm, jd)
    jy += 1595
    days = -355668 + (365 * jy) + ((jy / 33).floor * 8) + (((jy % 33) + 3) / 4).floor
    if jm < 7
      days += (jm - 1) * 31
    else
      days += ((jm - 7) * 30) + 186
    end
    days += jd - 1
    gy = 400 * (days / 146_097).floor
    days %= 146_097
    if days > 36_524
      days -= 1
      gy += 100 * (days / 36_524).floor
      days %= 36_524
      days += 1 if days >= 365
    end
    gy += 4 * (days / 1461).floor
    days %= 1461
    if days > 365
      gy += (days - 1) / 365
      days = (days - 1) % 365
    end
    gd = days + 1
    sal_a = [0, 31, ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    gm = 1
    while gm <= 12 && gd > sal_a[gm]
      gd -= sal_a[gm]
      gm += 1
    end
    [gy, gm, gd]
  end
end

# ---------- کلاس‌های کمکی ----------
class ReturnException < StandardError
  attr_reader :value
  def initialize(value = nil)
    @value = value
    super('return')
  end
end

class Percent
  attr_reader :value
  def initialize(value)
    @value = value / 100.0
  end

  def apply(number)
    number * @value
  end

  def to_s
    "#{@value * 100}%"
  end

  def inspect
    to_s
  end
end

class SoloDate
  attr_reader :is_jalali, :jalali_year, :jalali_month, :jalali_day, :gy, :gm, :gd

  def initialize(year, month, day, is_jalali = true)
    @is_jalali = is_jalali
    if is_jalali
      @jalali_year, @jalali_month, @jalali_day = year, month, day
      @gy, @gm, @gd = Jalali.jalali_to_gregorian(year, month, day)
    else
      @gy, @gm, @gd = year, month, day
      @jalali_year, @jalali_month, @jalali_day = Jalali.gregorian_to_jalali(year, month, day)
    end
  end

  def to_jalali_string
    format("%04d/%02d/%02d", @jalali_year, @jalali_month, @jalali_day)
  end

  def to_gregorian_string
    format("%04d/%02d/%02d", @gy, @gm, @gd)
  end

  def diff(other)
    d1 = Date.new(@gy, @gm, @gd)
    d2 = Date.new(other.gy, other.gm, other.gd)
    (d1 - d2).to_i
  end

  def year
    @is_jalali ? @jalali_year : @gy
  end

  def month
    @is_jalali ? @jalali_month : @gm
  end

  def day
    @is_jalali ? @jalali_day : @gd
  end

  def to_s
    to_jalali_string
  end

  def inspect
    to_s
  end

  def self.today
    today = Date.today
    jy, jm, jd = Jalali.gregorian_to_jalali(today.year, today.month, today.day)
    sd = SoloDate.new(jy, jm, jd, true)
    # تصحیح دستی تاریخ میلادی (برای سازگاری با نحوه ذخیره‌سازی در پایتون)
    sd.instance_variable_set(:@gy, today.year)
    sd.instance_variable_set(:@gm, today.month)
    sd.instance_variable_set(:@gd, today.day)
    sd
  end
end

class SoloArray
  include Enumerable

  attr_reader :items

  def initialize(items = [])
    @items = items.is_a?(Array) ? items.dup : []
  end

  def get(index)
    (index >= 1 && index <= @items.length) ? @items[index - 1] : nil
  end

  def set(index, value)
    if index >= 1 && index <= @items.length
      @items[index - 1] = value
      return true
    end
    false
  end

  def add(value)
    @items.push(value)
    self
  end

  def remove(index)
    if index >= 1 && index <= @items.length
      @items.delete_at(index - 1)
      return true
    end
    false
  end

  def length
    @items.length
  end

  def sum
    @items.select { |v| v.is_a?(Numeric) }.sum
  end

  def avg
    nums = @items.select { |v| v.is_a?(Numeric) }
    nums.empty? ? 0 : nums.sum / nums.length.to_f
  end

  def min
    nums = @items.select { |v| v.is_a?(Numeric) }
    nums.min
  end

  def max
    nums = @items.select { |v| v.is_a?(Numeric) }
    nums.max
  end

  def each(&block)
    @items.each(&block)
  end

  def to_s
    '[' + @items.map { |i| i.nil? ? 'null' : i.to_s }.join(', ') + ']'
  end

  def inspect
    to_s
  end
end

class SoloDict
  attr_reader :data

  def initialize(pairs = [])
    @data = {}
    pairs.each { |k, v| @data[k] = v } if pairs
  end

  def value(key)
    @data[key]
  end

  def key(val)
    @data.key(val)
  end

  def add(key, value)
    @data[key] = value
    self
  end

  def remove(key)
    if @data.key?(key)
      @data.delete(key)
      return true
    end
    false
  end

  def has(key)
    @data.key?(key)
  end

  def keys
    SoloArray.new(@data.keys)
  end

  def values
    SoloArray.new(@data.values)
  end

  def length
    @data.length
  end

  def to_s
    items = @data.map do |k, v|
      key_str = k.is_a?(String) ? "\"#{k}\"" : k.to_s
      "#{key_str}:#{v}"
    end
    '[' + items.join('; ') + ']'
  end

  def inspect
    to_s
  end
end

def smart_convert(value)
  return value unless value.is_a?(String)
  value = value.strip
  return nil if value.empty? || value.casecmp('null').zero?
  return true if value.casecmp('true').zero?
  return false if value.casecmp('false').zero?
  if value.end_with?('%')
    begin
      return Percent.new(Float(value[0..-2]))
    rescue
      return value
    end
  end
  Integer(value) rescue Float(value) rescue value
end

# ---------- FunctionHandler ----------
class FunctionHandler
  attr_reader :keywords, :functions

  def initialize
    @keywords = {
      'chap' => 'write',
      'set' => 'set',
      'agar' => 'when',
      'vagarna' => 'else',
      'loop' => 'loop',
      'baraye' => 'for',
      'az' => 'from',
      'ta' => 'to',
      'gam' => 'step',
      'dar' => 'in',
      'tabe' => 'function',
      'bargard' => 'return',
      'emtehan' => 'try',
      'khata' => 'error',
      'hamishe' => 'always',
      'ezafeBe' => 'add_to',
      'hazfAz' => 'remove_from',
      'shekan' => 'break',
      'edame' => 'continue',
      'begir' => 'input',
      'baghimande' => 'mod',
      'dorost' => 'true',
      'ghalat' => 'false',
      'hich' => 'null'
    }
    @functions = {}
  end

  def define(name, params, body_lines, default_values = {})
    @functions[name] = {
      params: params,
      body: body_lines,
      defaults: default_values
    }
  end

  def call(name, args, executor)
    return nil unless @functions.key?(name)
    func = @functions[name]
    params = func[:params]
    defaults = func[:defaults]
    body = func[:body]

    old_values = {}
    params.each do |param|
      old_values[param] = executor.variables.key?(param) ? executor.variables[param] : nil
    end

    params.each_with_index do |param, i|
      if i < args.length
        executor.set_variable(param, args[i])
      elsif defaults.key?(param)
        executor.set_variable(param, defaults[param])
      else
        executor.set_variable(param, nil)
      end
    end

    return_value = nil
    lines = body.split("\n")
    begin
      executor._execute_block(lines, 0, lines.length - 1)
    rescue ReturnException => e
      return_value = e.value
    rescue => e
      executor.error("Error in function '#{name}': #{e.message}")
    end

    params.each do |param|
      if !old_values[param].nil?
        executor.variables[param] = old_values[param]
      else
        executor.variables.delete(param)
      end
    end
    return_value
  end
end

# ---------- HP ----------
class HP
  attr_reader :variables, :colors, :function_handler, :builtins

  def initialize
    @variables = {}
    @colors = {
      'red' => "\e[91m",
      'green' => "\e[92m",
      'yellow' => "\e[93m",
      'blue' => "\e[94m",
      'purple' => "\e[95m",
      'cyan' => "\e[96m",
      'white' => "\e[97m",
      'reset' => "\e[0m"
    }
    @function_handler = FunctionHandler.new
    @builtins = {
      'sqrt' => ->(x) { Math.sqrt(x.to_f) },
      'int' => ->(x) { x.to_i },
      'float' => ->(x) { x.to_f },
      'str' => ->(x) { x.to_s },
      'bool' => ->(x) { !!x },
      'abs' => ->(x) { _is_number(x) ? x.to_f.abs : 0 }
    }
  end

  def translate(line)
    @function_handler.keywords.each do |hp, old|
      if line.match?(/\b#{Regexp.escape(hp)}\b/i)
        return line.gsub(/\b#{Regexp.escape(hp)}\b/i, old)
      end
    end
    line
  end

  def set_variable(name, value)
    @variables[name] = value
  end

  def error(msg)
    puts "#{@colors['red']}Error: #{msg}#{@colors['reset']}"
  end

  def color_text(text, color)
    "#{@colors[color] || ''}#{text}#{@colors['reset']}"
  end

  def _is_number(v)
    v.is_a?(Numeric)
  end

  def _to_num(v)
    case v
    when Numeric then v
    when TrueClass then 1
    when FalseClass then 0
    when Percent then v.value
    when String
      v.include?('.') ? v.to_f : v.to_i rescue v
    else v
    end
  end

  def _format_val(val)
    return 'null' if val.nil?
    return 'true' if val == true
    return 'false' if val == false
    return val.to_jalali_string if val.is_a?(SoloDate)
    return val.to_s if val.is_a?(Percent) || val.is_a?(SoloArray) || val.is_a?(SoloDict)
    val
  end

  def _evaluate_write_content(content)
    return '' if content.nil? || content.empty?
    val = _evaluate_expression(content)
    _format_val(val).to_s
  end

  def _evaluate_expression(expr)
    expr = expr.to_s.strip
    return '' if expr.empty?

    # رشته‌ها
    return expr[1..-2] if (expr.start_with?('"') && expr.end_with?('"')) ||
                          (expr.start_with?("'") && expr.end_with?("'"))

    # ثابت‌ها
    return nil if expr.casecmp('null').zero?
    return true if expr.casecmp('true').zero?
    return false if expr.casecmp('false').zero?

    # پرانتز
    if expr.start_with?('(')
      depth = 0
      close_idx = -1
      expr.chars.each_with_index do |ch, i|
        depth += 1 if ch == '('
        depth -= 1 if ch == ')'
        if depth == 0
          close_idx = i
          break
        end
      end
      return _evaluate_expression(expr[1...close_idx]) if close_idx == expr.length - 1
    end

    # درصد
    if expr.end_with?('%') && !expr.start_with?('$')
      begin
        return Percent.new(Float(expr[0..-2]))
      rescue
        # ignore
      end
    end

    # تاریخ
    return SoloDate.today if expr == '@today'
    m = expr.match(/^@(\d{4})\/(\d{2})\/(\d{2})$/)
    return SoloDate.new(m[1].to_i, m[2].to_i, m[3].to_i, true) if m
    m = expr.match(/^@@(\d{4})\/(\d{2})\/(\d{2})$/)
    return SoloDate.new(m[1].to_i, m[2].to_i, m[3].to_i, false) if m

    # فاکتوریل
    if expr.end_with?('!') && !expr.start_with?('!!')
      v = _evaluate_expression(expr[0..-2])
      num = v.to_i
      if num < 0
        error("Factorial of negative is undefined")
        return 0
      end
      (1..num).reduce(1, :*)
    end

    # قدرمطلق
    if expr.start_with?('|') && expr.end_with?('|')
      v = _evaluate_expression(expr[1..-2])
      return v.abs if v.is_a?(Numeric)
      error("abs error")
      return 0
    end

    # مثلثات
    %w[sin cos tan].each do |func|
      m = expr.match(/\$#{func}\((.+)\)$/)
      if m
        v = _evaluate_expression(m[1])
        return Math.send(func, v * Math::PI / 180) if v.is_a?(Numeric)
        error("#{func} needs number")
        return 0
      end
    end

    # لگاریتم
    m = expr.match(/\$log\((.+)\)$/)
    if m
      v = _evaluate_expression(m[1])
      return Math.log10(v) if v.is_a?(Numeric) && v > 0
      error("log needs positive")
      return 0
    end

    # gcd / lcm
    m = expr.match(/\$gcd\((.+),(.+)\)$/)
    if m
      a = _evaluate_expression(m[1].strip).to_i
      b = _evaluate_expression(m[2].strip).to_i
      return a.gcd(b)
    end
    m = expr.match(/\$lcm\((.+),(.+)\)$/)
    if m
      a = _evaluate_expression(m[1].strip).to_i
      b = _evaluate_expression(m[2].strip).to_i
      return a.lcm(b)
    end

    # متد شیء
    m = expr.match(/^(\w+)\.(\w+)\((.*)\)$/)
    if m && @variables.key?(m[1])
      obj = @variables[m[1]]
      args_str = m[3]
      args = args_str.strip.empty? ? [] : _parse_args(args_str)
      result = _call_object_method(obj, m[2], args)
      return result unless result.nil?
    end

    # فراخوانی تابع
    m = expr.match(/^(\w+)\((.*)\)$/)
    if m
      fname = m[1]
      args = _parse_args(m[2])
      if @function_handler.functions.key?(fname)
        return @function_handler.call(fname, args, self)
      elsif @builtins.key?(fname)
        begin
          return @builtins[fname].call(*args)
        rescue
          error("call #{fname} failed")
          return nil
        end
      end
    end

    # آرایه/دیکشنری
    if expr.start_with?('[') && expr.end_with?(']')
      content = expr[1..-2].strip
      if content.include?(':')
        return _parse_dict(content)
      else
        items = content.empty? ? [] : _parse_args(content)
        return SoloArray.new(items)
      end
    end

    # ویژگی شیء
    m = expr.match(/^(\w+)\.(\w+)$/)
    if m && @variables.key?(m[1])
      obj = @variables[m[1]]
      attr = m[2]
      case obj
      when SoloArray
        return obj.length if attr == 'length'
        return obj.sum if attr == 'sum'
        return obj.avg if attr == 'avg'
        return obj.min if attr == 'min'
        return obj.max if attr == 'max'
      when SoloDict
        return obj.length if attr == 'length'
        return obj.keys if attr == 'keys'
        return obj.values if attr == 'values'
      when String
        return obj.length if attr == 'length'
        return obj.upcase if attr == 'upper'
        return obj.downcase if attr == 'lower'
      when SoloDate
        return obj.year if attr == 'year'
        return obj.month if attr == 'month'
        return obj.day if attr == 'day'
      end
      return nil
    end

    # دسترسی با ایندکس
    m = expr.match(/^(\w+)\[(\d+)\]$/)
    if m && @variables.key?(m[1]) && @variables[m[1]].is_a?(SoloArray)
      return @variables[m[1]].get(m[2].to_i)
    end

    # متغیر ساده
    return @variables[expr] if @variables.key?(expr)

    # توابع تجمعی
    %w[length sum avg min max].each do |func|
      m = expr.match(/^#{func}\((\w+)\)$/)
      if m && @variables.key?(m[1]) && @variables[m[1]].is_a?(SoloArray)
        return @variables[m[1]].send(func)
      elsif m
        return func == 'min' || func == 'max' ? nil : 0
      end
    end

    # اعداد
    return Integer(expr) rescue Float(expr) rescue nil if expr.match?(/^-?\d+(\.\d+)?$/)

    # sqrt / root قدیمی
    m = expr.match(/^sqrt\((.+)\)$/)
    if m
      v = _evaluate_expression(m[1])
      return Math.sqrt(v) if v.is_a?(Numeric)
      error("sqrt error")
      return 0
    end
    m = expr.match(/^root\((.+),(.+)\)$/)
    if m
      v = _evaluate_expression(m[1])
      n = _evaluate_expression(m[2])
      return v ** (1.0 / n) if v.is_a?(Numeric) && n.is_a?(Numeric)
      error("root error")
      return 0
    end

    # مقایسه‌ها
    %w[<= >= != == < >].each do |op|
      if expr.include?(op)
        idx = expr.index(op)
        left = expr[0...idx].strip
        right = expr[idx + op.length..-1].strip
        lv = _evaluate_expression(left)
        rv = _evaluate_expression(right)
        lv = lv.value if lv.is_a?(Percent)
        rv = rv.value if rv.is_a?(Percent)
        lv = _to_num(lv)
        rv = _to_num(rv)
        if _is_number(lv) && _is_number(rv)
          return lv.send(op, rv)
        else
          return lv.to_s.send(op, rv.to_s)
        end
      end
    end

    # توان
    if expr.include?('^') && !expr.include?('"')
      b, e = expr.split('^', 2)
      bv = _to_num(_evaluate_expression(b.strip))
      ev = _to_num(_evaluate_expression(e.strip))
      return bv ** ev
    end

    # باقیمانده
    if expr.include?(' mod ')
      parts = expr.split(' mod ', 2)
      lv = _to_num(_evaluate_expression(parts[0].strip))
      rv = _to_num(_evaluate_expression(parts[1].strip))
      raise ZeroDivisionError, "integer modulo by zero" if rv == 0
      return lv % rv
    end

    # ضرب و تقسیم
    %w[* /].each do |op|
      if expr.include?(op)
        l, r = expr.split(op, 2)
        lv = _evaluate_expression(l.strip)
        rv = _evaluate_expression(r.strip)
        lv = lv.value if lv.is_a?(Percent)
        rv = rv.value if rv.is_a?(Percent)
        raise ZeroDivisionError, "division by zero" if op == '/' && rv == 0
        if op == '*' && lv.is_a?(String) && rv.is_a?(Integer)
          return lv * rv
        end
        if op == '*' && rv.is_a?(String) && lv.is_a?(Integer)
          return rv * lv
        end
        return lv.send(op, rv) if _is_number(lv) && _is_number(rv)
        return lv.to_s + rv.to_s
      end
    end

    # جمع و تفریق
    %w[+ -].each do |op|
      if expr.include?(op)
        l, r = expr.split(op, 2)
        lv = _evaluate_expression(l.strip)
        rv = _evaluate_expression(r.strip)
        if lv.is_a?(SoloDate) && rv.is_a?(SoloDate) && op == '-'
          return lv.diff(rv)
        end
        lv = lv.value if lv.is_a?(Percent)
        rv = rv.value if rv.is_a?(Percent)
        return lv.to_s + rv.to_s if lv.is_a?(String) || rv.is_a?(String)
        return lv.send(op, rv) if _is_number(lv) && _is_number(rv)
        return lv.to_s + rv.to_s
      end
    end

    expr
  end

  def evaluate_expression(expr)
    _evaluate_expression(expr)
  end

  def _call_object_method(obj, method_name, args)
    case obj
    when SoloArray
      case method_name
      when 'get' then args.empty? ? nil : obj.get(args[0])
      when 'set' then args.length >= 2 ? obj.set(args[0], args[1]) : nil
      when 'add' then obj.add(args[0]) if args.any?; obj
      when 'remove' then args.empty? ? nil : obj.remove(args[0])
      when 'length' then obj.length
      when 'sum' then obj.sum
      when 'avg' then obj.avg
      when 'min' then obj.min
      when 'max' then obj.max
      end
    when SoloDict
      case method_name
      when 'value' then args.empty? ? nil : obj.value(args[0])
      when 'key' then args.empty? ? nil : obj.key(args[0])
      when 'add' then obj.add(args[0], args[1]) if args.length >= 2; obj
      when 'remove' then args.empty? ? nil : obj.remove(args[0])
      when 'has' then args.empty? ? nil : obj.has(args[0])
      when 'keys' then obj.keys
      when 'values' then obj.values
      when 'length' then obj.length
      end
    when String
      case method_name
      when 'length' then obj.length
      when 'upper' then obj.upcase
      when 'lower' then obj.downcase
      end
    when SoloDate
      case method_name
      when 'year' then obj.year
      when 'month' then obj.month
      when 'day' then obj.day
      end
    end
  rescue
    nil
  end

  def _parse_args(s)
    return [] if s.strip.empty?
    args = []
    cur = ''
    in_q = false
    quote_char = nil
    depth = 0
    s.each_char do |ch|
      if %w[" '].include?(ch)
        if !in_q
          in_q = true
          quote_char = ch
          cur << ch
        elsif ch == quote_char
          in_q = false
          quote_char = nil
          cur << ch
        else
          cur << ch
        end
      elsif '([{'.include?(ch) && !in_q
        depth += 1
        cur << ch
      elsif ')]}'.include?(ch) && !in_q
        depth -= 1
        cur << ch
      elsif ch == ',' && depth == 0 && !in_q
        args << _evaluate_expression(cur.strip)
        cur = ''
      else
        cur << ch
      end
    end
    args << _evaluate_expression(cur.strip) unless cur.strip.empty?
    args
  end

  def _parse_dict(content)
    pairs = []
    _split_semicolon(content).each do |pair|
      if pair.include?(':')
        k, v = pair.split(':', 2)
        key = k.strip.gsub(/^"(.*)"$/, '\1').gsub(/^'(.*)'$/, '\1')
        val = _evaluate_expression(v.strip)
        pairs << [key, val]
      end
    end
    SoloDict.new(pairs)
  end

  def _split_semicolon(text)
    parts = []
    cur = ''
    in_q = false
    quote_char = nil
    text.each_char do |ch|
      if %w[" '].include?(ch)
        if !in_q
          in_q = true
          quote_char = ch
          cur << ch
        elsif ch == quote_char
          in_q = false
          quote_char = nil
          cur << ch
        else
          cur << ch
        end
      elsif ch == ';' && !in_q
        parts << cur.strip
        cur = ''
      else
        cur << ch
      end
    end
    parts << cur.strip unless cur.strip.empty?
    parts
  end

  def find_matching_brace(lines, start)
    depth = 0
    (start...lines.length).each do |i|
      depth += lines[i].count('{') - lines[i].count('}')
      return i if depth == 0
    end
    lines.length - 1
  end

  def find_else_for_when(lines, when_start)
    depth = 1
    (when_start + 1...lines.length).each do |i|
      line = lines[i].strip
      depth += line.count('{') - line.count('}')
      return i if depth == 1 && line.include?('else')
      if depth == 0
        return i if line.include?('else')
        if i + 1 < lines.length
          next_line = lines[i + 1].strip
          return i + 1 if next_line.start_with?('else')
        end
        return nil
      end
    end
    nil
  end

  def find_matching_function_end(lines, start)
    (start + 1...lines.length).each do |i|
      return i if lines[i].include?('}f')
    end
    lines.length - 1
  end

  def _execute_block(lines, start, last)
    i = start
    while i <= last
      line = lines[i].strip
      line = translate(line)
      if line.empty? || ['{', '}'].include?(line) || line.include?('} else') || line == 'else' || line.start_with?('else {') || line == '}f'
        i += 1
        next
      end
      begin
        if line.start_with?('when ')
          i = _execute_when(lines, i)
        elsif line.start_with?('loop ')
          i = _execute_loop(lines, i)
        elsif line.start_with?('for ')
          i = _execute_for_loop(lines, i)
        elsif line.start_with?('function ')
          i = _execute_function_def(lines, i)
        elsif line.start_with?('try ')
          i = _execute_try(lines, i)
        else
          _execute_line(line)
          i += 1
        end
      rescue ReturnException => e
        raise e
      end
    end
  end

  def _execute_when(lines, idx)
    line = lines[idx].strip
    cond = line.include?('{') ? line[5...line.index('{')].strip : line[5..-1].strip
    body_start = idx
    body_start = idx + 1 unless lines[idx].include?('{')
    body_end = find_matching_brace(lines, body_start)
    else_idx = find_else_for_when(lines, idx)

    if _evaluate_expression(cond)
      if lines[idx].include?('{')
        _execute_block(lines, idx + 1, body_end - 1)
      else
        _execute_block(lines, idx + 2, body_end - 1)
      end
      return body_end + 1
    elsif else_idx
      else_line = lines[else_idx].strip
      if else_line.include?('{')
        else_block_start = else_idx + 1
        else_block_end = find_matching_brace(lines, else_idx)
        _execute_block(lines, else_block_start, else_block_end - 1)
        return else_block_end + 1
      else
        else_body_start = else_idx + 1
        else_body_end = find_matching_brace(lines, else_body_start)
        _execute_block(lines, else_idx + 2, else_body_end - 1)
        return else_body_end + 1
      end
    else
      return body_end + 1
    end
  rescue ReturnException => e
    raise e
  end

  def _execute_loop(lines, idx)
    line = lines[idx].strip
    cond = line.include?('{') ? line[5...line.index('{')].strip : line[5..-1].strip
    s = idx + 1
    e = find_matching_brace(lines, idx)
    while _evaluate_expression(cond)
      begin
        _execute_block(lines, s, e - 1)
      rescue ReturnException => e
        raise e
      end
    end
    e
  end

  def _execute_for_loop(lines, idx)
    line = lines[idx].strip.delete('{').strip
    m = line.match(/^for\s+(\w+)\s*~\s*(.+)/)
    unless m
      error("invalid for loop")
      return find_matching_brace(lines, idx)
    end
    var, rng = m[1], m[2].strip
    s = idx + 1
    e = find_matching_brace(lines, idx)

    run_loop = ->(items) {
      items.each do |item|
        set_variable(var, item)
        begin
          _execute_block(lines, s, e - 1)
        rescue ReturnException => ex
          raise ex
        end
      end
    }

    ftp = rng.match(/^from\s+(.+)\s+to\s+(.+)\s+step\s+(.+)/)
    if ftp
      st = _evaluate_expression(ftp[1]).to_i
      en = _evaluate_expression(ftp[2]).to_i
      step = _evaluate_expression(ftp[3]).to_i
      range = step > 0 ? (st..en).step(step) : (st.downto(en).step(-step).to_a) # simplified
      run_loop.call(range)
      return e
    end

    ft = rng.match(/^from\s+(.+)\s+to\s+(.+)/)
    if ft
      st = _evaluate_expression(ft[1]).to_i
      en = _evaluate_expression(ft[2]).to_i
      range = st <= en ? (st..en).to_a : st.downto(en).to_a
      run_loop.call(range)
      return e
    end

    ia = rng.match(/^in\s+(.+)/)
    if ia
      container_name = ia[1].strip
      if @variables.key?(container_name)
        container = @variables[container_name]
        items = case container
                when SoloArray then container.items
                when SoloDict then container.data.keys
                when String then container.chars
                else []
                end
        run_loop.call(items)
      end
      return e
    end

    error("invalid for range")
    e
  end

  def _execute_function_def(lines, idx)
    line = lines[idx].strip
    m = line.match(/^function\s+(\w+)\s*\((.*)\)\s*f{/)
    unless m
      error("invalid function def")
      return find_matching_brace(lines, idx)
    end
    name = m[1]
    params_str = m[2].strip
    params = []
    defaults = {}
    unless params_str.empty?
      params_str.split(',').each do |p|
        p = p.strip
        if p.include?('=')
          n, v = p.split('=', 2)
          params << n.strip
          defaults[n.strip] = _evaluate_expression(v.strip)
        else
          params << p
        end
      end
    end
    block_end = find_matching_function_end(lines, idx)
    body = lines[idx + 1...block_end].join("\n")
    @function_handler.define(name, params, body, defaults)
    block_end + 1
  end

  def _execute_try(lines, idx)
    try_end = find_matching_brace(lines, idx)
    try_lines = lines[idx + 1...try_end]
    error_occurred = false
    begin
      _execute_block(try_lines, 0, try_lines.length - 1)
    rescue ReturnException => e
      raise e
    rescue => e
      error_occurred = true
    end

    i = try_end + 1
    while i < lines.length
      l = lines[i].strip
      if l.start_with?('error')
        if error_occurred
          if l.include?('{')
            s = i + 1
            e = find_matching_brace(lines, i)
            _execute_block(lines, s, e - 1)
          elsif i + 1 < lines.length && lines[i + 1].include?('{')
            s = i + 2
            e = find_matching_brace(lines, i + 1)
            _execute_block(lines, s, e - 1)
          end
        end
        i = _skip_block(lines, i)
      elsif l.start_with?('always')
        if l.include?('{')
          s = i + 1
          e = find_matching_brace(lines, i)
          _execute_block(lines, s, e - 1)
        elsif i + 1 < lines.length && lines[i + 1].include?('{')
          s = i + 2
          e = find_matching_brace(lines, i + 1)
          _execute_block(lines, s, e - 1)
        end
        i = _skip_block(lines, i)
      else
        break
      end
      i += 1
    end
    i
  end

  def _skip_block(lines, i)
    if lines[i].include?('{')
      find_matching_brace(lines, i)
    elsif i + 1 < lines.length && lines[i + 1].include?('{')
      find_matching_brace(lines, i + 1)
    else
      i
    end
  end

  def _execute_line(line)
    line = translate(line)
    line = line[0...line.index('...')].strip if line.include?('...')
    return nil if line.empty?

    if line.start_with?('write ')
      content = line[6..-1].strip
      cm = content.match(/^(red|green|yellow|blue|purple|cyan|white)\((.+)\)$/)
      if cm
        color, inner = cm[1], cm[2].strip
        result = _evaluate_write_content(inner)
        puts color_text(result, color)
      else
        puts _evaluate_write_content(content)
      end
      return nil
    end

    if line.start_with?('set ')
      m = line.match(/^set\s+(\w+)\s*=\s*(.+)/)
      if m
        vn = m[1]
        vs = m[2].strip
        if vs.start_with?('input')
          pm = vs.match(/input\s*\(\s*"([^"]*)"\s*\)/)
          prompt = pm ? pm[1] : ''
          print prompt
          val = smart_convert(gets.chomp)
        else
          val = _evaluate_expression(vs)
        end
        set_variable(vn, val)
      end
      return nil
    end

    if line.start_with?('add_to ')
      m = line.match(/^add_to\s+(\w+)\s+(.+)/)
      if m && @variables[m[1]].is_a?(SoloArray)
        @variables[m[1]].add(_evaluate_expression(m[2].strip))
      end
      return nil
    end

    if line.start_with?('remove_from ')
      m = line.match(/^remove_from\s+(\w+)\s+(\d+)/)
      if m && @variables[m[1]].is_a?(SoloArray)
        @variables[m[1]].remove(m[2].to_i)
      end
      return nil
    end

    if line.include?('=') && !line.start_with?('set ')
      m = line.match(/^(\w+)\s*=\s*(.+)/)
      if m
        vn = m[1]
        vs = m[2].strip
        if @variables.key?(vn)
          if vs.start_with?('input')
            pm = vs.match(/input\s*\(\s*"([^"]*)"\s*\)/)
            prompt = pm ? pm[1] : ''
            print prompt
            val = smart_convert(gets.chomp)
            set_variable(vn, val)
          else
            set_variable(vn, _evaluate_expression(vs))
          end
        else
          error("undefined variable '#{vn}'")
        end
        return nil
      end
    end

    if @variables.key?(line)
      puts _format_val(@variables[line])
      return nil
    end

    raise ReturnException.new(nil) if line == 'return'
    raise ReturnException.new(_evaluate_expression(line[7..-1].strip)) if line.start_with?('return ')

    res = _evaluate_expression(line)
    if !res.nil? && res != line
      puts _format_val(res)
    end
    nil
  end

  def execute_code(code_str)
    lines = code_str.split("\n").map(&:rstrip)
    i = 0
    while i < lines.length
      line = lines[i].strip
      if line.empty? || ['{', '}'].include?(line) || line.start_with?('} else') || line == 'else' || line.start_with?('else {') || line == '}f'
        i += 1
        next
      end
      if line.start_with?('when ')
        i = _execute_when(lines, i)
      elsif line.start_with?('loop ')
        i = _execute_loop(lines, i)
      elsif line.start_with?('for ')
        i = _execute_for_loop(lines, i)
      elsif line.start_with?('function ')
        i = _execute_function_def(lines, i)
      elsif line.start_with?('try ')
        i = _execute_try(lines, i)
      else
        begin
          _execute_line(line)
        rescue ReturnException
          # برگشت از تابع
        end
        i += 1
      end
    end
  end

  def RUN(filename)
    unless filename.downcase.end_with?('.hp')
      error("Only .hp files are supported!")
      return false
    end
    begin
      content = File.read(filename, encoding: 'utf-8')
      puts "HP v1.0.0 - Running #{filename}"
      puts '─' * 30
      execute_code(content)
      puts '─' * 30
      puts "Execution finished."
      true
    rescue Errno::ENOENT
      error("file '#{filename}' not found")
      false
    rescue => e
      error(e.message)
      puts e.backtrace
      false
    end
  end
end

# ---------- اجرای برنامه ----------
if __FILE__ == $0
  hp = HP.new
  if ARGV.length > 0
    hp.RUN(ARGV[0])
  else
    print 'FileName: '
    filename = gets.chomp
    system('clear') || system('cls')
    hp.RUN(filename)
  end
end
