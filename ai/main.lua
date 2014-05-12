dofile("global.lua")

function display_map(map)
	for i = 1, #map do
		for k, v in pairs(map[i]) do
			io.write(map[i][k])
			nb = tonumber(map[i][k])
			if (nb ~= nil) then
				if (nb > 9) then
					io.write("  ")
				else
					io.write("   ")
				end
			else
				io.write("   ")
			end
		end
		io.write("\n")
	end
end

function get_abs_dist(entities, x, y, i, j)
	return math.abs(entities[i]["x"] - x + entities[i]["y"] - y)
end

function have_elem(entities, x, y)
	for i = 1, #entities do
		if (get_abs_dist(entities, x, y, i) <= AGGRO) then
			return 1
		end
	end
	return 0
end

function random_movement()
	local mov = {1, -1, 1, -1}
	local n = math.random(1, 4)
	if (n == 1 or n == 2) then
		X = X + mov[n]
	else
		Y = Y + mov[n]
	end
	print("new x: " .. X .. " -- new y: " .. Y)
end

-- function get_shortest_priority(map, x, y)
-- 	local dist = AGGRO
-- 	if (x > 0 and type(map[y][x]) == "number") then
-- 		if (map[y][x]) then
			
-- 		end
-- 	end
-- 	if (x < MAP_XMAX + 1) then
-- 	end
-- 	if (y > 0) then
-- 	end
-- 	if (y < MAP_YMAX + 1) then
-- 	end

-- end

-- function get_shortest_priority(map, entities)
-- 	-- priority to
-- 	-- priority to M and P
-- 	-- next X
-- 	-- next B
-- 	-- next random direction

-- 	local dist = {{}}

-- 	for i = 1, #entities do
-- 		dist[i]["type"] = entities[i]["type"]
-- 		dist[i]["nb"] = get_shortest_distance_of(map, entities[i]["x"], entities[i]["y"])
-- 	end



-- end

function get_nb_from(c)
	if (c == "M" or c == "P") then
		return 1
	end
	return tonumber(c)
end

function check_directions(map, cur_x, cur_y, i_x, i_y)
	local move = 0
	local nb = nil
	for i = 1, (AGGRO * 2) + 1 do
		if (nb ~= nil and (map[cur_y][cur_x] == "." or type(map[cur_y][cur_x]) == "number")) then
			if (nb + 1 > AGGRO and map[cur_y][cur_x] ~= nb - 1) then return move end
			if (type(map[cur_y][cur_x]) == "number" and (nb + 1 < tonumber(map[cur_y][cur_x]))) then
				map[cur_y][cur_x] = nb + 1
				move = move + 1
			elseif (map[cur_y][cur_x] == ".") then
				map[cur_y][cur_x] = nb + 1
				move = move + 1
			end
		end
		nb = tonumber(map[cur_y][cur_x])
		cur_x = cur_x + i_x
		cur_y = cur_y + i_y
		if (cur_y == 0 or cur_y == MAP_YMAX + 1) then return move end
		if (cur_x == 0 or cur_x == MAP_XMAX + 1) then return move end
	end
	return move
end

function init_direction(map, n1, n2, i_x, i_y, d_x, d_y)
	local cur_x = n1
	local cur_y = n2
	local move = 0
	for i = 1, AGGRO * 2 do
		move = move + check_directions(map, cur_x, cur_y, i_x, i_y)
		cur_x = cur_x + d_x
		cur_y = cur_y + d_y
		if (cur_x == MAP_XMAX + 1) then break end
		if (cur_y == MAP_YMAX + 1) then break end
	end
	return move
end

function go_all_directions(map, cur_x, cur_y)
	local n1 = cur_x - AGGRO
	if (n1 <= 0) then n1 = 1 end
	local n2 = cur_x + AGGRO
	if (n2 > MAP_XMAX) then n2 = MAP_XMAX end
	local n3 = cur_y - AGGRO
	if (n3 <= 0) then n3 = 1 end
	local n4 = cur_y + AGGRO
	if (n4 > MAP_YMAX) then n4 = MAP_YMAX end

	local move = 0
	move = move + init_direction(map, n1, n4, 0, -1, 1, 0) --up
	move = move + init_direction(map, n1, n3, 0, 1, 1, 0) -- down
	move = move + init_direction(map, n1, n3, 1, 0, 0, 1) -- right
	move = move + init_direction(map, n2, n3, -1, 0, 0, 1) -- left

	if (move ~= 0) then
		return 1
	end
	return 0
end

function travel_map(map, cur_x, cur_y)
	local move = 0
	map[cur_y][cur_x] = "0"
	move = move + check_directions(map, cur_x, cur_y, 0, -1)
	move = move + check_directions(map, cur_x, cur_y, 0, 1)
	move = move + check_directions(map, cur_x, cur_y, 1, 0)
	move = move + check_directions(map, cur_x, cur_y, -1, 0)
	if (move == 0) then	return 0 end
	move = 1
	while (move == 1) do
		move = go_all_directions(map, cur_x, cur_y)
	end
end

function best_first(map, entities)
	local cur_x, cur_y = X, Y
	if (have_elem(entities, cur_x, cur_y)) then
		travel_map(map, cur_x, cur_y)
		-- get_shortest_priority(map, entities)
	else
		random_movement()
	end
end

function pathfinding()
	local entities = {
		{["type"] = 1, ["x"] = 4, ["y"] = 10}, 	-- player
		-- {["type"] = 2, ["x"] = X, ["y"] = Y},	-- me the monster
		{["type"] = 2, ["x"] = 6, ["y"] = 3},	-- monster 2
		{["type"] = 4, ["x"] = 8, ["y"] = 4},	-- box
		{["type"] = 3, ["x"] = 4, ["y"] = 2},	-- box bonus
	}
	local map = {
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"},
		{"W", ".", "W", "X", "W", ".", ".", "W", ".", "W"},
		{"W", ".", "W", ".", "W", "M", ".", "W", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", "B", ".", "W"},
		{"W", ".", "W", ".", "W", "W", "W", ".", ".", "W"},
		{"W", ".", "W", ".", ".", "M", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", "P", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", ".", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"}
	}
	display_map(map)
	best_first(map, entities)

	print("\nFINAL MAP\n")
	display_map(map)
end

X, Y = 6, 6

pathfinding()

a = add(12, 12)
print(a)
