function can_i_put_bomb(map_nb, x, y, block)
	local cur_x, cur_y = x, y
	local way = 0
	local gotox = {0, 0, -1, 1}
	local gotoy = {-1, 1, 0, 0}

	for i = 1, BOMB_RANGE + 1 do
		if (block[1] == 0) then
			if (cur_y - i > 0 and map_nb[cur_y - i][cur_x] ~= ".") then block[1] = 1
			elseif (cur_y - i > 0 and map_nb[cur_y - i][cur_x] == ".") then way = 1
			else break end
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[2] == 0) then
			if (cur_x - i > 0 and map_nb[cur_y][cur_x - i] ~= ".") then block[2] = 1
			elseif (cur_x - i > 0 and map_nb[cur_y][cur_x - i] == ".") then way = 3
			else break end
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[3] == 0) then
			if (cur_y + i < MAP_YMAX and map_nb[cur_y + i][cur_x] ~= ".") then block[3] = 1
			elseif (cur_y + i < MAP_YMAX and map_nb[cur_y + i][cur_x] == ".") then way = 2
			else break end
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[4] == 0) then
			if (cur_x + i < MAP_XMAX and map_nb[cur_y][cur_x + i] ~= ".") then block[4] = 1
			elseif (cur_x + i < MAP_XMAX and map_nb[cur_y][cur_x + i] == ".") then way = 4
			else break end
		end
	end
	if (way ~= 0) then
		x = x + gotox[way]
		y = y + gotoy[way]
	end
	return x, y
end

function run_out_danger(map, x, y)
	local cur_x, cur_y = x, y
	local way = 0
	local gotox = {0, 0, -1, 1}
	local gotoy = {-1, 1, 0, 0}

	if (cur_y - 1 > 0 and map[cur_y - 1][cur_x] == ".") then way = 1 end
	if (cur_x - 1 > 0 and map[cur_y][cur_x - 1] == ".") then way = 3 end
	if (cur_y + 1 < MAP_YMAX and map[cur_y + 1][cur_x] == ".") then way = 2 end
	if (cur_x + 1 < MAP_XMAX and map[cur_y][cur_x + 1] == ".") then way = 4 end
	if (way ~= 0) then
		x = x + gotox[way]
		y = y + gotoy[way]
	end
	return x, y
end

function random_movement(map)
	local orient = arg["orientation"] + 1
	local mov = {1, 1, -1, -1}
	local tested = {0, 0, 0, 0}
	local x, y = X, Y
	local i

	if (orient == 1 or orient == 3) then y = y + mov[orient] end
	if (orient == 2 or orient == 4) then x = x + mov[orient] end
	if (map[y][x] == ".") then return x, y end
	for i = 0, 3 do
		x = X
		y = Y
		local n = math.random(1, 4)
		local save = 0
		local j = 1
		while (j < 5 and (n > 0 or save == 0)) do
			if (tested[j] == 0) then
				save = j
				n = n - 1
			end
			j = j + 1
		end
		tested[save] = 1
		if (save == 1 or save == 3) then y = y + mov[save] end
		if (save == 2 or save == 4) then x = x + mov[save] end
		if (map[y][x] == ".") then return x, y end
	end
	return x, y
end
