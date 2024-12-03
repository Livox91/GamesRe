function GenerateQuads(atlas,tilewidth,tileheight)
    local sheetwidth = atlas:getWidth() / tilewidth
    local sheetheight = atlas:getHeight() / tileheight

    local sheetcounter = 1
    local spritesheet = {}

    for y = 0 , sheetheight-1 do 
        for x = 0 , sheetwidth-1 do
            spritesheet[sheetcounter] = 
            love.graphics.newQuad(x*tilewidth ,y*tileheight, tilewidth, tileheight, atlas:getDimensions())

            sheetcounter = sheetcounter+1

        end

    end

    return spritesheet

end

function table.slice(tbl,first,last,step)
    local sliced = {}

    for i = 1 or first , last or #tbl , step or 1 do 
        sliced[#sliced+1] = tbl[i]
    end

    return sliced 
    
end

function GenerateQuadBrick(atlas)
    return table.slice(GenerateQuads(atlas,32,16),1,21)    
end

function GenerateQuadPaddles(atlas)
    local y= 64
    local x= 0
    local counter = 1 
    local Quad = {}

    for i = 0 , 3 do
        Quad[counter] = love.graphics.newQuad(x,y,32,16,atlas:getDimensions())
        counter = counter+1
        Quad[counter] = love.graphics.newQuad(x+32,y,64,16,atlas:getDimensions())
        counter = counter+1
        Quad[counter] = love.graphics.newQuad(x+96,y,96,16,atlas:getDimensions())
        counter = counter+1
        Quad[counter] = love.graphics.newQuad(x,y+16,128,16,atlas:getDimensions())
        counter = counter+1

        x = 0 
        y = y+32
    end
    
    return Quad    
end

function GenerateQuadBall(atlas)
    local y = 48 
    local x = 96

    local counter = 1
    local Quad = {}
    
    for i = 0 ,3 do 
        Quad[counter] = love.graphics.newQuad(x,y,8,8, atlas:getDimensions())
        x = x + 8
        counter = counter + 1
    end
    x = 96
    y = 56
    for i = 0 ,2 do
        Quad[counter] = love.graphics.newQuad(x,y, 8, 8,atlas:getDimensions())
        x = x + 8
        counter = counter + 1
    end
    return Quad
end
