function get_shortest_distance_of(map, x, y)
	local cur_dist = AGGRO + 1
	local cur_x, cur_y = 0, 0

	if (x - 1 > 0 and type(map[y][x - 1]) == "number") then
		if (map[y][x - 1] < cur_dist) then 
			cur_dist = map[y][x - 1]
			cur_x, cur_y = x - 1, y
		end
	end
	if (x + 1 < MAP_XMAX + 1 and type(map[y][x + 1]) == "number") then
		if (map[y][x + 1] < cur_dist) then
			cur_dist = map[y][x + 1]
			cur_x, cur_y = x + 1, y
		end
	end
	if (y - 1 > 0 and type(map[y - 1][x]) == "number") then
		if (map[y - 1][x] < cur_dist) then
			cur_dist = map[y - 1][x]
			cur_x, cur_y = x, y - 1
		end
	end
	if (y + 1 < MAP_YMAX + 1 and type(map[y + 1][x]) == "number") then
		if (map[y + 1][x] < cur_dist) then
			cur_dist = map[y + 1][x]
			cur_x, cur_y = x, y + 1
		end
	end
	return cur_dist, cur_x, cur_y
end

function get_good_way(map, x, y, nb)
	if (x - 1 > 0 and type(map[y][x - 1]) == "number") then
		if (map[y][x - 1] < nb) then return y, x - 1 end
	end
	if (x + 1 < MAP_XMAX + 1 and type(map[y][x + 1]) == "number") then
		if (map[y][x + 1] < nb) then return y, x + 1 end
	end
	if (y - 1 > 0 and type(map[y - 1][x]) == "number") then
		if (map[y - 1][x] < nb) then return y - 1, x end
	end
	if (y + 1 < MAP_YMAX + 1 and type(map[y + 1][x]) == "number") then
		if (map[y + 1][x] < nb) then return y + 1, x end
	end
end

function take_shortest_priority(map, entities)
	local x, tmp_x = 1000000, 1000000
	local y, tmp_y = 1000000, 1000000
	local cur_dist = 0
	local min_dist = 50
	local t = 4

	for i = 1, #entities do
		if (entities[i]["type"] ~= 6 and entities[i]["type"] ~= 7 and (entities[i]["x"] ~= X or entities[i]["y"] ~= Y)) then
			cur_dist, tmp_x, tmp_y = get_shortest_distance_of(map, entities[i]["x"], entities[i]["y"])
			if (cur_dist ~= AGGRO + 1 and tmp_x ~= 0 and tmp_y ~= 0) then
				if (entities[i]["type"] < t) then
					min_dist = 50
					t = entities[i]["type"]
				end
				if (min_dist > cur_dist and entities[i]["type"] == t) then
					x, y = tmp_x, tmp_y
					min_dist = cur_dist
				end
			end
		end
	end
	while (map[y][x] ~= 0 and map[y][x] ~= 1) do
		y, x = get_good_way(map, x, y, map[y][x])
	end
	return x, y
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
		print("\nFINAL MAP\n")
		display_map(map)
		cur_x, cur_y = take_shortest_priority(map, entities)
		print("\ndirection is : x y : ", cur_x, cur_y, "")
		print("\n--------------------------------------\n")
	else
		cur_x, cur_y = random_movement()
	end
end
