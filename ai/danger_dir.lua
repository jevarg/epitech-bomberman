function right_danger(map, cur_x, cur_y, n, e)
	if (cur_x + n < MAP_XMAX + 1 and map[cur_y][cur_x + n] ~= "O") then
		if (authorized_ent_danger(map, cur_x, cur_y, 0, n) == 1) then
			if (map[cur_y][cur_x + n] == "I") then
				map[cur_y][cur_x + n] = e
				return
			else return end
		else map[cur_y][cur_x + n] = e end
	end
end

function left_danger(map, cur_x, cur_y, n, e)
	if (cur_x - n > 0 and map[cur_y][cur_x - n] ~= "O") then
		if (authorized_ent_danger(map, cur_x, cur_y, 0, n * (-1)) == 1) then
			if (map[cur_y][cur_x - n] == "I") then
				map[cur_y][cur_x - n] = e
				return
			else return end
		else map[cur_y][cur_x - n] = e end
	end
end

function down_danger(map, cur_x, cur_y, n, e)
	if (cur_y + n < MAP_YMAX + 1 and map[cur_y + n][cur_x] ~= "O") then
		if (authorized_ent_danger(map, cur_x, cur_y, n, 0) == 1) then
			if (map[cur_y + n][cur_x] == "I") then
				map[cur_y + n][cur_x] = e
				return
			else return end
		else map[cur_y + n][cur_x] = e end
	end
end

function up_danger(map, cur_x, cur_y, n, e)
	if (cur_y - n > 0 and map[cur_y - n][cur_x] ~= "O") then
		if (authorized_ent_danger(map, cur_x, cur_y, n * (-1), 0) == 1) then
			if (map[cur_y - n][cur_x] == "I") then
				map[cur_y - n][cur_x] = e
				return
			else return end
		else map[cur_y - n][cur_x] = e end
	end
end