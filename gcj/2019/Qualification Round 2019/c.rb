t = STDIN.gets.to_i

t.times{|test_case|
  n, l = STDIN.gets.split.map(&:to_i)
  dat = STDIN.gets.split.map(&:to_i)
  
  ans = Array.new(l+1)


  (l+10).times{
    (l-1).times{|i|
      g = dat[i].gcd(dat[i+1])

      if g==dat[i] then
        if !ans[i].nil? then
          ans[i+1] = dat[i] / ans[i]
          ans[i+2] = dat[i+1] / ans[i+1]
        elsif !ans[i+2].nil? then
          ans[i+1] = dat[i+1] / ans[i+2]
          ans[i] = dat[i] / ans[i+1]
        end
        
      else
        ans[i] = dat[i] / g
        ans[i+1] = g
        ans[i+2] = dat[i+1] / g
      end
    } 
  }

  temp = ans.clone()
  temp.sort!().uniq!()

  ans = ans.map{|p| 65+temp.find_index(p)}.pack("c*")
  
  puts "Case ##{test_case+1}: #{ans}"
}


