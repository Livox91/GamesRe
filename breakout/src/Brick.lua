Brick = Class{}

PalletColors = {
    [1] = {
        ['r'] = 99,
        ['g'] = 155,
        ['b'] = 255
    },

    [2] = {
        ['r'] = 106,
        ['g'] = 190,
        ['b'] = 47
    },

    [3] = {
        ['r'] = 217,
        ['g'] = 87,
        ['b'] = 99
    },
    
    [4] = {
        ['r'] = 215,
        ['g'] = 123,
        ['b'] = 186
    },

    [5] = {
        ['r'] = 251,
        ['g'] = 242,
        ['b'] = 52
    },
}

function Brick:init(x,y)
    self.tier = 0
    self.color = 1 

    self.x = x
    self.y = y
    self.width = 32
    self.height = 16
    
    self.inplay = true

    self.psystem = love.graphics.newParticleSystem(gTexture['particle'],64)

    self.psystem:setParticleLifetime(0.5 ,1)
    self.psystem:setLinearAcceleration(-15,0,15,80)
    self.psystem:setEmissionArea('normal',10,10)
    
end

function Brick:hit()


    self.psystem:setColors(
        PalletColors[self.color].r / 255,
        PalletColors[self.color].g / 255,
        PalletColors[self.color].b / 255,
        55 * (self.tier + 1) / 255,
        PalletColors[self.color].r / 255,
        PalletColors[self.color].g / 255,
        PalletColors[self.color].b / 255,
        0
    )
    self.psystem:emit(64)

    gSounds['brick-hit-2']:stop()
    gSounds['brick-hit-2']:play()
    
    if self.tier > 0 then
        if self.color == 1 then
            self.tier = self.tier -1 
            self.color = 5
        else
            self.color = self.color -1
        end
    else

        if self.color ==1 then 
            self.inplay = false
        else    
            self.color = self.color - 1
        end
    end

    if not self.inplay then
        gSounds['brick-hit-1']:stop()
        gSounds['brick-hit-1']:play()
    end
end

function Brick:render()

    if self.inplay then
        love.graphics.draw(gTexture['main'],gFrames['bricks'][1+((self.color-1)*4)+self.tier],self.x,self.y )
    end
    
end

function Brick:renderParticles()
    love.graphics.draw(self.psystem,self.x+16,self.y +8)
    
end