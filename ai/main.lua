dofile("global.lua")

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

function get_max_priority(entities, dist, typ)
	-- priority to
	-- all pos MONSTER and PLAYER
	-- priority to M and P
	-- next X
	-- next B
	-- next random direction

	local cur_pr = 0
	for i = 1, #dist + 1 do

	end
	return (dist[cur_pr])
end

function have_elem(entities, opened)
	local cur_dist = 0
	for i = 1, #entities do
		for j = 1, #opened do
			cur_dist = math.abs(entities[i]["x"] - opened[j]["x"])
					   + math.abs(entities[i]["y"] - opened[j]["y"])
			print(cur_dist)
			if (cur_dist <= AGGRO) then
				return 1
			end
		end
	end
	return 0
end

function best_first(map, entities)
	local cur_x, cur_y = X, Y
	local opened = {
		{["x"] = cur_x, ["y"] = cur_y}
	}
	print(#opened)
	while (#opened > 0) do
		if (have_elem(entities, opened)) then
			-- if ((cur_elem = get_best_elem(entities, opened)) == 0) then
			-- 	random_movement()
			-- 	return
			-- end
			print("have an elem")
			return
		else
			print("no element, random movement")
			random_movement()
			return
		end
	end
end

function pathfinding()
	local entities = {
		{["type"] = 1, ["x"] = 2, ["y"] = 2}, 	-- player
		-- {["type"] = 2, ["x"] = X, ["y"] = Y},	-- me the monster
		{["type"] = 2, ["x"] = 6, ["y"] = 3},	-- monster 2
		{["type"] = 4, ["x"] = 8, ["y"] = 4},	-- box
		{["type"] = 3, ["x"] = 4, ["y"] = 2},	-- box bonus
	}
	print(AGGRO)
	local map = {
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"},
		{"W", "P", "W", "X", "W", ".", ".", "W", ".", "W"},
		{"W", ".", "W", ".", "W", "M", ".", "W", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", "B", ".", "W"},
		{"W", ".", "W", ".", "W", "W", "W", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", "M", ".", "W"},
		{"W", ".", "W", "W", "W", ".", ".", ".", ".", "W"},
		{"W", ".", ".", ".", ".", ".", ".", ".", ".", "W"},
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"}
	}
	display_map(map)
	best_first(map, entities)
	display_map(map)
end

X, Y = 8, 7

pathfinding()

a = add(12, 12)
print(a)
