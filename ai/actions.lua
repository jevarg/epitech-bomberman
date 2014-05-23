function run_out_danger(map, x, y, nb)
	-- if (map[y][x] == ".") then
	-- 	return
	-- end
	-- if (nb < BOMB_RANGE + 1) then
	-- 	if (y + 1 < MAP_YMAX and map[y + 1][x] ~= "W" and map[y + 1][x] ~= "B") then
	-- 		go_out_danger(map, x, y + 1, nb + 1)
	-- 	end
	-- 	if (y - 1 > 0 and map[y - 1][x] ~= "W" and map[y - 1][x] ~= "B") then
	-- 		go_out_danger(map, x, y - 1, nb + 1)
	-- 	end
	-- 	if (x + 1 < MAP_YMAX and map[y][x + 1] ~= "W" and map[y][x + 1] ~= "B") then
	-- 		go_out_danger(map, x + 1, y, nb + 1)
	-- 	end
	-- 	if (x - 1 > 0 and map[y][x - 1] ~= "W" and map[y][x - 1] ~= "B") then
	-- 		go_out_danger(map, x - 1, y, nb + 1)
	-- 	end
	-- end
end

function random_movement(map, used_nb)
	local orient = arg["orientation"] + 1
	local mov = {-1, -1, 1, 1}
	local tested = {0, 0, 0, 0}
	local x, y = X, Y
	local i

	print("orient:" , orient - 1)
	if (orient == 1 or orient == 3) then y = y + mov[orient] end
	if (orient == 2 or orient == 4) then x = x + mov[orient] end
	if (map[y][x] == ".") then
		return x, y
	else
		print ("not true")
	end	
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
		print("random value:" , save)
		tested[save] = 1
		if (orient == 1 or orient == 3) then y = y + mov[orient]
		elseif (orient == 2 or orient == 4) then x = x + mov[orient] end
		if (map[y][x] == ".") then
			return x, y
		else
			print ("not true")
		end
	end
	return x, y	
	--[[
	if (n == 1 or n == 2) then
		x = X + mov[n]
		if (x < 1) then x = 1 end
		if (x > MAP_XMAX) then x = MAP_XMAX end
	else
		y = Y + mov[n]
		if (y < 1) then y = 1 end
		if (y > MAP_YMAX) then y = MAP_YMAX end
	end
	if (map[y][x] ~= ".") then
		table.insert(used_nb, n)
		x, y = random_movement(map, used_nb)
		return x, y
	end
	return x, y
	--]]
end
