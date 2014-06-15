function authorized_put_bomb(point, map, boolean)
	if (map[Y][X] == "O" or boolean == true) then
		if (point ~= "." and point ~= "I" and point ~= "D") then
			return 1
		end
		return 0
	elseif (point ~= "." and point ~= "I") then
		return 1
	end
	return 0
end

function search_safe_place(map_nb, x, y, block, boolean, cond)
	-- print("search_safe_place")
	local nb = 50
	local way = 0
	local gotox = {0, 0, -1, 1}
	local gotoy = {-1, 1, 0, 0}

	-- print("IN  ? MAP AFTER fill_dangerous_fields")
	-- display_map(map_nb)

	for i = 1, cond do
		if (block[1] == 0) then
			if (y - i < 1 or authorized_put_bomb(map_nb[y - i][x], map_nb, boolean) == 1) then block[1] = 1
			elseif (map_nb[y - i][x] == ".") then if (i < nb) then nb = i ; way = 1 ; break end
			elseif (x - 1 > 0 and map_nb[y - i][x - 1] == ".") then if (i < nb) then nb = i ; way = 1 ; break end
			elseif (x + 1 < MAP_XMAX and map_nb[y - i][x + 1] == ".") then if (i < nb) then nb = i ; way = 1 ; break end
			end
		else break end
	end
	for i = 1, cond do
		if (block[2] == 0) then
			if (x - i < 1 or authorized_put_bomb(map_nb[y][x - i], map_nb, boolean) == 1) then block[2] = 1
			elseif (map_nb[y][x - i] == ".") then if (i < nb) then nb = i ; way = 3 ; break end
			elseif (y - 1 > 0 and map_nb[y - 1][x - i] == ".") then if (i < nb) then nb = i ; way = 3 ; break end
			elseif (y + 1 < MAP_YMAX and map_nb[y + 1][x - i] == ".") then if (i < nb) then nb = i ; way = 3 ; break end
			end
		else break end
	end
	for i = 1, cond do
		if (block[3] == 0) then
			if (y + i > MAP_YMAX or authorized_put_bomb(map_nb[y + i][x], map_nb, boolean) == 1) then block[3] = 1
			elseif (map_nb[y + i][x] == ".") then if (i < nb) then nb = i ; way = 2 ; break end
			elseif (x - 1 > 0 and map_nb[y + i][x - 1] == ".") then if (i < nb) then nb = i ; way = 2 ; break end
			elseif (x + 1 < MAP_XMAX and map_nb[y + i][x + 1] == ".") then if (i < nb) then nb = i ; way = 2 ; break end
			end
		else break end
	end
	for i = 1, cond do
		if (block[4] == 0) then
			if (x + i > MAP_XMAX or authorized_put_bomb(map_nb[y][x + i], map_nb, boolean) == 1) then block[4] = 1
			elseif (map_nb[y][x + i] == ".") then if (i < nb) then nb = i ; way = 4 ; break end
			elseif (y - 1 > 0 and map_nb[y - 1][x + i] == ".") then if (i < nb) then nb = i ; way = 4 ; break end
			elseif (y + 1 < MAP_YMAX and map_nb[y + 1][x + i] == ".") then if (i < nb) then nb = i ; way = 4 ; break end
			end
		else break end
	end
	-- print("WAY IS ", way)
	if (way ~= 0) then
		x = x + gotox[way]
		y = y + gotoy[way]
	end
	return x, y
end

function can_i_put_bomb(map_nb, x, y, block)
	-- print("can i put bomb ?")
	local way = 0
	local gotox = {0, 0, -1, 1}
	local gotoy = {-1, 1, 0, 0}

	map_nb = fill_dangerous_fields(map_nb)
	for i = 1, BOMB_RANGE + 1 do
		if (block[1] == 0) then
			if (y - i < 1 or authorized_put_bomb(map_nb[y - 1][x], map_nb, false) == 1) then block[1] = 1
			elseif (i == BOMB_RANGE + 1 and map_nb[y - i][x] == ".") then way = 1 ; break
			elseif (x - 1 > 0 and map_nb[y - i][x - 1] == ".") then way = 1 ; break
			elseif (x + 1 < MAP_XMAX and map_nb[y - i][x + 1] == ".") then way = 1 ; break
			end
		else break end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[2] == 0) then
			if (x - i < 1 or authorized_put_bomb(map_nb[y][x - i], map_nb, false) == 1) then block[2] = 1
			elseif (i == BOMB_RANGE  + 1 and map_nb[y][x - i] == ".") then way = 3 ; break
			elseif (y - 1 > 0 and map_nb[y - 1][x - i] == ".") then way = 3 ; break
			elseif (y + 1 < MAP_YMAX and map_nb[y + 1][x - i] == ".") then way = 3 ; break
			end
		else break end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[3] == 0) then
			if (y + i > MAP_YMAX or authorized_put_bomb(map_nb[y + i][x], map_nb, false) == 1) then block[3] = 1
			elseif (i == BOMB_RANGE + 1 and map_nb[y + i][x] == ".") then way = 2 ; break
			elseif (x - 1 > 0 and map_nb[y + i][x - 1] == ".") then way = 2 ; break
			elseif (x + 1 < MAP_XMAX and map_nb[y + i][x + 1] == ".") then way = 2 ; break
			end
		else break end
	end
	for i = 1, BOMB_RANGE + 1 do
		if (block[4] == 0) then
			if (x + i > MAP_XMAX or authorized_put_bomb(map_nb[y][x + i], map_nb, false) == 1) then block[4] = 1
			elseif (i == BOMB_RANGE + 1 and map_nb[y][x + i] == ".") then way = 4 ; break
			elseif (y - 1 > 0 and map_nb[y - 1][x + i] == ".") then way = 4 ; break
			elseif (y + 1 < MAP_YMAX and map_nb[y + 1][x + i] == ".") then way = 4 ; break 
			end
		else break end
	end
	-- print("way is ", way)
	if (way ~= 0) then
		x = x + gotox[way]
		y = y + gotoy[way]
	end
	return x, y
end

function run_out_danger(map_nb, x, y, block)
	-- print("run out danger !")
	if (arg["bomb"] == 1) then
		map_nb[y][x] = "O"
		map_nb = fill_dangerous_fields(map_nb)
	end
	local tmpx, tmpy = 0, 0
	tmpx, tmpy = search_safe_place(map_nb, x, y, block, false, BOMB_RANGE + 1)
	if (tmpx == x and tmpy == y) then
		return search_safe_place(map_nb, x, y, block, true, BOMB_RANGE)
	end
	return tmpx, tmpy
end

function get_orient(map)
	local orient = arg["orientation"] + 1
	local mov = {1, 1, -1, -1}
	local tested = {0, 0, 0, 0}
	local x, y = X, Y
	local i	
	
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

function random_movement(map)
	-- print("random")
	local mov = {1, 1, -1, -1}
	local orient = arg["orientation"] + 1
	local x, y = X, Y
	local dirX = 0
	local dirY = 0
	
	if (orient == 1 or orient == 3) then
		dirY = mov[orient]
	end
	if (orient == 2 or orient == 4) then
		dirX = mov[orient]
	end
	x = x + dirX
	y = y + dirY
	if (map[y][x] == ".") then
		local tx, ty = get_orient(map)
		if (tx == X - dirX and ty == Y - dirY) then -- Taking a wrong direction
			return x, y
		elseif (math.random() * 100 < 10) then
			return tx, ty
		end
		return x, y
	end
	return get_orient(map)
end
