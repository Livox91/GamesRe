


NONE = 1 
SINGLE_PYRAMID = 2
MULTI_PYRAMID = 3

SOLID= 1
SKIP= 2
ALTERNATE = 3
NONE = 4


LevelMaker = Class{}



function LevelMaker.createmap(level)

    local brick = {}

    local numRows = math.random(1,5)
    local numCols = math.random(7, 13)
    numCols = numCols % 2 == 0 and (numCols+1) or numCols

    local Highest_tier = math.min(3,math.floor(level/5))
    local Highest_color = math.min(5,level % 5 + 3)
    
    for y = 1 ,numRows   do

        local skip_pattern = math.random(2) == 1 and true or false
        local alternate_pattern = math.random(2) == 1 and true or false
        
        local AlternateColor1 = math.random(0,Highest_color)
        local AlternateColor2 = math.random(0,Highest_color)
        local AlternateTier1 = math.random(0,Highest_tier)
        local AlternateTier2 = math.random(0,Highest_tier)

        local skipFlag = math.random(2) == 1 and true or false
        local alternateFlag = math.random(2) == 1 and true or false

        local solidColor = math.random(1, Highest_color)
        local solidTier = math.random(0,Highest_tier)

        for x= 1 , numCols   do

            if skipFlag and skip_pattern then
                skipFlag = not skipFlag

                goto continue
            else
                skipFlag = not skipFlag
            end

            b = Brick((x-1) * 32 + 8 + (13-numCols) * 16 , y * 16 )

            if alternate_pattern and alternateFlag then 
                b.color = AlternateColor1
                b.tier = AlternateTier1
                alternateFlag = not alternateFlag
            else
                b.color = AlternateColor2
                b.tier = AlternateTier2
                alternateFlag = not alternateFlag
            end

            if not alternate_pattern then
                b.color = solidColor
                b.tier = solidTier
            end


            table.insert(brick,b)
            ::continue::
        end 
    end
    if #brick == 0  then 
        return self.createmap(level)
    else
        return brick
    end 

end