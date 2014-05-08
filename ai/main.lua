-- function execute_ia(x, y)
-- 	MAP_XMAX = x
-- 	MAP_YMAX = y
-- end

function display_map(map)
	for i = 1, #map do
		for k, v in pairs(map[i]) do
			io.write(map[i][k])
			io.write(" ")
		end
		io.write("\n")
	end
end

function touched(map, x, y)
	if (map[x][y] == "P") then
		return 0
	end
	return 1
end

function contamine(map, x, y)
	local touch = 0
	local cur_x, cur_y = x, y
	local cur_nb = 0

	while (touch) do
	end
end

function pathfinding()
	p_x, p_y = 2, 2
	m_x, m_y = 9, 9

	map = {
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"},
		{"W", "P", "W", ".", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", "W", ".", "W"},
		{"W", ".", "W", ".", "W", "W", "W", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", "M", ".", "W"},
		{"W", ".", "W", "W", "W", ".", ".", ".", ".", "W"},
		{"W", ".", ".", ".", ".", ".", ".", ".", ".", "W"},
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"}
	}
	display_map(map)
--	contamine(map, m_x, m_y)
	display_map(map)
end

pathfinding()

a = add(12, 12)
print(a)
