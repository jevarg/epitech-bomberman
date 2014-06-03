function run_out_danger(map, x, y, nb)
	if (map[y][x] == ".") then X_TMP, Y_TMP = x, y end
	if (nb < BOMB_RANGE + 1) then
		if (y + 1 < MAP_YMAX and map[y + 1][x] ~= "W" and map[y + 1][x] ~= "B") then
			run_out_danger(map, x, y + 1, nb + 1) end
		if (y - 1 > 0 and map[y - 1][x] ~= "W" and map[y - 1][x] ~= "B") then
			run_out_danger(map, x, y - 1, nb + 1) end
		if (x + 1 < MAP_YMAX and map[y][x + 1] ~= "W" and map[y][x + 1] ~= "B") then
			run_out_danger(map, x + 1, y, nb + 1) end
		if (x - 1 > 0 and map[y][x - 1] ~= "W" and map[y][x - 1] ~= "B") then
			run_out_danger(map, x - 1, y, nb + 1) end
	end
	if (X_TMP == 0 and Y_TMP == 0) then X_TMP, Y_TMP = x, y end
end

function random_movement(map)
	local orient = arg["orientation"] + 1
	local mov = {1, 1, -1, -1}
	local tested = {0, 0, 0, 0}
	local x, y = X, Y
	local i

	if (orient == 1 or orient == 3) then y = y + mov[orient] end
	if (orient == 2 or orient == 4) then x = x + mov[orient] end
	if (map[y][x] == ".") then return x, y
		else print("else:", map[y][x], x, y, orient) end
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
