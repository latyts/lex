require 'readline'

def lex(input)
  tokens = []
  start = 0
  forward = 0
  buf = ''

  while start < input.length do
    c = input[start]
    token = []
    if c.match?(/[[:digit:]]/)
      buf += c
      n = 1
      forward = start + n
      while forward < input.length do
        nc = input[forward]
        if nc.match?(/[[:digit:]]/)
          buf += nc
          n += 1
          forward = start + n
        else
          break
        end
      end
      token = [[:number, buf]]
      tokens += token
      buf = ''
      start = start + n
    elsif c == '+'
      tokens += [[:plus, nil]]
      start += 1
    elsif c.strip.empty?
      start += 1
    else
      puts 'unknown token ' + c
      break
    end
  end

  tokens
end

while buf = Readline.readline('> ', true) do
  p lex(buf)
end
