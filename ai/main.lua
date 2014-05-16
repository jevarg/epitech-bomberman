dofile("ai/global.lua")
dofile("ai/utils.lua")
dofile("ai/best_first.lua")

function check_bomb(map)
	return true
end

function check_character(map)
	return true
end

function create_map(entities, aggro)
	local map = {}

	for i = 1, aggro do
		table.insert(map, {})
		for j = 1, aggro do
			table.insert(map[i], " ")
		end
	end

	for i = 1, #entities do
		if (entities[i]["type"] == 0) then
			map[entities[i]["y"]][entities[i]["x"]] = "W"
		elseif (entities[i]["type"] == 2) then
			map[entities[i]["y"]][entities[i]["x"]] = "."
		elseif (entities[i]["type"] == 1) then
			map[entities[i]["y"]][entities[i]["x"]] = "P"
		elseif (entities[i]["type"] == 4) then
			map[entities[i]["y"]][entities[i]["x"]] = "B"
		end
	end
	return map
end

function artificial_intelligence()
	local entities = {}
	local translate = {
		[0] = 0,
		[1] = TYPE_PRIORITY["box"],
		[2] = 2,
		[4] = TYPE_PRIORITY["player"]
	}

	for i = 1, #arg, 3 do
		table.insert(entities, {["type"] = translate[arg[i]], ["y"] = arg[i + 1], ["x"] = arg[i + 2]})
	end
	local map = create_map(entities, arg["aggro"])
	display_map(map)
	if (check_bomb(map) and check_character(map)) then
		best_first(map, entities)
	end
end

X, Y = arg["x"], arg["y"]
AGGRO = arg["aggro"]
MAP_XMAX = AGGRO
MAP_YMAX = AGGRO
artificial_intelligence()
