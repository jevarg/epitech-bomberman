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

function get_entities()
	local translate = {
		[0] = TYPE_PRIORITY["wall"],
		[1] = TYPE_PRIORITY["free"],
		[2] = TYPE_PRIORITY["box"],
		[3] = TYPE_PRIORITY["bomb"],
		[4] = TYPE_PRIORITY["danger"],
		[6] = TYPE_PRIORITY["free"],
		[7] = TYPE_PRIORITY["item"],
		[8] = TYPE_PRIORITY["item"],
		[9] = TYPE_PRIORITY["item"],
		[10] = TYPE_PRIORITY["item"],
		[11] = TYPE_PRIORITY["player"],
		[12] = TYPE_PRIORITY["player"],
		[13] = TYPE_PRIORITY["player"],
		[14] = TYPE_PRIORITY["player"]
	}
	local ent = {}
	local entities = {}
	local m = 1
	for i = 1, #arg, 3 do
		table.insert(ent, {["type"] = translate[arg[i]], ["y"] = arg[i + 1], ["x"] = arg[i + 2]})
		m = m + 1
	end
	for i = 1, 8 do
		for j = 1, #ent do
			if (ent[j]["type"] == i) then
				table.insert(entities, ent[j])
			end
		end
	end
	return entities
end

function set_priority(level)
	if (level == 1) then
		player, item, box, bomb, wall, free, danger = 2, 3, 1, 4, 5, 6, 7
	elseif (level == 2) then
		player, item, box, bomb, wall, free, danger = 1, 2, 3, 4, 5, 6, 7
	elseif (level == 3) then
		player, item, box, bomb, wall, free, danger = 2, 1, 3, 4, 5, 6, 7
	end
	TYPE_PRIORITY = {
		["player"] = player,
		["item"] = item,
		["box"] = box,
		["bomb"] = bomb,
		["wall"] = wall,
		["free"] = free,
		["danger"] = danger
	}
end
