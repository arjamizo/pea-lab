f=File.new('tests.bat','w')
tests_types=['LB','swap','worse','all']
f.puts "PATH=%PATH%;#{Dir.getwd.gsub('/','\\')}\\..\\przegZup-CB\\bin\\Release"
tests=Dir.glob('*.txt')
.delete_if{|x| !(x=~/\d+\.txt/)}
.sort{|a,b| a.scan(/\d+/)[0].to_i<=>b.scan(/\d+/)[0].to_i}
#puts tests.inspect; exit
tests_types.each{|type|
	tests.each{|fle|
	next if !(fle=~/[0-9]+\.txt/)
		f.puts "przegZup #{fle} #{type}"
	}
}
f.close
