function authorized_put_bomb(point)
	if (point ~= "." and point ~= "I" and point ~= "D") then
		return 1
	end
	return 0
end

function can_i_put_bomb(map_nb, x, y, block)
	local way = 0
	local gotox = {0, 0, -1, 1}
	local gotoy = {-1, 1, 0, 0}

	-- print("can i put bomb ?")
	map_nb = fill_dangerous_fields(map_nb)
	-- display_map(map_nb)
	for i = 1, BOMB_RANGE + 1 do
		if (block[1] == 0) then
			if (y - i < 1 or authorized_put_bomb(map_nb[y - 1][x]) == 1) then block[1] = 1
			elseif (i == BOMB_RANGE + 1 and map_nb[y - i][x] == ".") then print("find at :", y - i, x) ; way = 1 ; break
			elseif (x - 1 > 0 and map_nb[y - i][x - 1] == ".") then print("find at :", y - i, x - 1) ; way = 1 ; break
			elseif (x + 1 < MAP_XMAX + 1 and map_nb[y - i][x + 1] == ".") then print("find at :", y - i, x + 1) ; way = 1 ; break
			end
		else
			break
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[2] == 0) then
			if (x - i < 1 or authorized_put_bomb(map_nb[y][x - i]) == 1) then block[2] = 1
			elseif (i == BOMB_RANGE  + 1 and map_nb[y][x - i] == ".") then print("find at :", y, x - i) ; way = 3 ; break
			elseif (y - 1 > 0 and map_nb[y - 1][x - i] == ".") then print("find at :", y - 1, x - i) ; way = 3 ; break
			elseif (y + 1 < MAP_YMAX + 1 and map_nb[y + 1][x - i] == ".") then print("find at :", y + 1, x - i) ; way = 3 ; break
			end
		else
			break
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[3] == 0) then
			if (y + i > MAP_YMAX or authorized_put_bomb(map_nb[y + i][x]) == 1) then block[3] = 1
			elseif (i == BOMB_RANGE + 1 and map_nb[y + i][x] == ".") then print("find at :", y + i, x) ; way = 2 ; break
			elseif (x - 1 > 0 and map_nb[y + i][x - 1] == ".") then print("find at :", y + i, x - 1) ; way = 2 ; break
			elseif (x + 1 < MAP_XMAX + 1 and map_nb[y + i][x + 1] == ".") then print("find at :", y + i, x + 1) ; way = 2 ; break
			end
		else
			break
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[4] == 0) then
			if (x + i > MAP_XMAX or authorized_put_bomb(map_nb[y][x + i]) == 1) then block[4] = 1
			elseif (i == BOMB_RANGE + 1 and map_nb[y][x + i] == ".") then print("find at :", y, x + i) ; way = 4 ; break
			elseif (y - 1 > 0 and map_nb[y - 1][x + i] == ".") then print("find at :", y - 1, x + i) ; way = 4 ; break
			elseif (y + 1 < MAP_YMAX + 1 and map_nb[y + 1][x + i] == ".") then print("find at :", y + 1, x + i) ; way = 4 ; break 
			end
			else
			break
		end
	end
	print("way is : ", way)
	if (way ~= 0) then
		x = x + gotox[way]
		y = y + gotoy[way]
	end
	return x, y
end

function run_out_danger(map_nb, x, y, block)
	local nb = 50
	local way = 0
	local gotox = {0, 0, -1, 1}
	local gotoy = {-1, 1, 0, 0}


	-- print("run out danger", x, y)
	if (arg["bomb"] == 1) then map_nb[y][x] = "O" end
	map_nb = fill_dangerous_fields(map_nb)

	-- display_map(map_nb)

	for i = 1, BOMB_RANGE + 1 do
		if (block[1] == 0) then
			if (y - i < 1 or authorized_put_bomb(map_nb[y - i][x]) == 1) then block[1] = 1
			elseif (map_nb[y - i][x] == ".") then if (i < nb) then print("find at :", y - i, x) ; nb = i ; way = 1 ; break end
			elseif (x - 1 > 0 and map_nb[y - i][x - 1] == ".") then if (i < nb) then print("find at :", y - i, x - 1) ; nb = i ; way = 1 ; break end
			elseif (x + 1 < MAP_XMAX + 1 and map_nb[y - i][x + 1] == ".") then if (i < nb) then print("find at :", y - i, x + 1) ; nb = i ; way = 1 ; break end
			end
		else
			break
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[2] == 0) then
			if (x - i < 1 or authorized_put_bomb(map_nb[y][x - i]) == 1) then block[2] = 1
			elseif (map_nb[y][x - i] == ".") then if (i < nb) then print("find at :", y, x - i) ; nb = i ; way = 3 ; break end
			elseif (y - 1 > 0 and map_nb[y - 1][x - i] == ".") then if (i < nb) then print("find at :", y - 1, x - i) ; nb = i ; way = 3 ; break end
			elseif (y + 1 < MAP_YMAX + 1 and map_nb[y + 1][x - i] == ".") then if (i < nb) then print("find at :", y + 1, x - i) ; nb = i ; way = 3 ; break end
			end
		else
			break
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[3] == 0) then
			if (y + i > MAP_YMAX or authorized_put_bomb(map_nb[y + i][x]) == 1) then block[3] = 1
			elseif (map_nb[y + i][x] == ".") then if (i < nb) then print("find at :", y + i, x) ; nb = i ; way = 2 ; break end
			elseif (x - 1 > 0 and map_nb[y + i][x - 1] == ".") then if (i < nb) then print("find at :", y + i, x - 1) ; nb = i ; way = 2 ; break end
			elseif (x + 1 < MAP_XMAX + 1 and map_nb[y + i][x + 1] == ".") then if (i < nb) then print("find at :", y + i, x + 1) ; nb = i ; way = 2 ; break end
			end
		else
			break
		end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[4] == 0) then
			if (x + i > MAP_XMAX or authorized_put_bomb(map_nb[y][x + i]) == 1) then block[4] = 1
			elseif (map_nb[y][x + i] == ".") then if (i < nb) then print("find at :", y, x + i) ; nb = i ; way = 4 ; break end
			elseif (y - 1 > 0 and map_nb[y - 1][x + i] == ".") then if (i < nb) then print("find at :", y - 1, x + i) ; nb = i ; way = 4 ; break end
			elseif (y + 1 < MAP_YMAX + 1 and map_nb[y + 1][x + i] == ".") then if (i < nb) then print("find at :", y + 1, x + i) ; nb = i ; way = 4 ; break end
			end
		else
			break
		end
	end
	print("WAY IS : ", way)
	if (way ~= 0) then
		x = x + gotox[way]
		y = y + gotoy[way]
	end
	return x, y
end

function random_movement(map)
	print("random move")
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
