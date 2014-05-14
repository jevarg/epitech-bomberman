dofile("global.lua")
dofile("utils.lua")
dofile("best_first.lua")

function check_bomb(map)
	return true
end

function check_character(map)
	return true
end

function artificial_intelligence()

	local entities = {
		{["type"] = 1, ["x"] = 4, ["y"] = 10}, 	-- player
		{["type"] = 2, ["x"] = 6, ["y"] = 3},	-- monster 2
		{["type"] = 4, ["x"] = 8, ["y"] = 4},	-- box
		{["type"] = 3, ["x"] = 4, ["y"] = 2},	-- box bonus
		{["type"] = 5, ["x"] = 7, ["y"] = 10}	-- bomb
	}
	local map = {
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"},
		{"W", ".", "W", "X", "W", ".", ".", "W", ".", "W"},
		{"W", ".", "W", ".", "W", "M", ".", "W", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", "B", ".", "W"},
		{"W", ".", "W", ".", "W", "W", "W", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", "W", ".", "W"},
		{"W", ".", "W", "P", "W", ".", "B", "M", ".", "W"},
		{"W", ".", "W", ".", "W", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", ".", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", ".", "W", ".", ".", ".", ".", ".", ".", "W"},
		{"W", "W", "W", "W", "W", "W", "W", "W", "W", "W"}
	}

	display_map(map)
	if (check_bomb(map) and check_character(map)) then
		best_first(map, entities)
	end
end

X, Y = 8, 10
artificial_intelligence()
