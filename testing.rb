#!/usr/bin/ruby

data = "2#6'&78)5+1/AT[NJ_PERLQO@IAHPNSMBJCKLRMSDHEJNPOQFKGIQLSNF@DBROPMAGCEMPOACSRQDF"

mikes = [
	"UF! ",
	"UR! ",
	"UB! ",
	"UL! ",
	"DF! ",
	"DR! ",
	"DB! ",
	"DL! ",
	"FR! ",
	"FL! ",
	"BR! ",
	"BL! ",
	"UFR!",
	"URB!",
	"UBL!",
	"ULF!",
	"DRF!",
	"DFL!",
	"DLB!",
	"DBR!"
]

values = mikes.map do |cubie|
	val = cubie[0].getbyte(0) ^ cubie[1].getbyte(0) ^ cubie[2].getbyte(0)
	puts "#{cubie} #{val}"
	val
end

puts values.inspect
puts (values === values.uniq).inspect

data_values = values.map do |val|
	data.index(val.chr)
end

puts data_values.inspect

values = mikes.map do |cubie|
	val = cubie[0].getbyte(0) ^ cubie[1].getbyte(0) ^ cubie[2].getbyte(0)
	x = [cubie.index('U').to_i, cubie.index('D').to_i].min
	puts "#{cubie} #{val} #{data.index(val.chr)} #{~x ? x : x < cubie[0] > 70}"
	val
end
