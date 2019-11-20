import pygame



class PONG:
    width = 800
    height = 600
    black = (0,0,0)
    white = (255,255,255)
    gameDisplay = pygame.display.set_mode((width, height))

    def __init__(self):
        pygame.init()
        self.clock=pygame.time.Clock()
        self.bar=Bar()
        self.gameLoop()
    
    def gameLoop(self):
        terminarjuego=False
        while not terminarjuego:
            for evento in pygame.event.get():
                if evento.type == pygame.QUIT:
                    terminarjuego==True
            teclas= pygame.key.get_pressed()
            self.bar.ballcenterx+=self.bar.ballvelx
            self.bar.ballcentery+=self.bar.ballvely
            print(self.bar.barx)            
            
            #si toca el techo, rebota hacia abajo
            if (self.bar.ballcentery+self.bar.radio)>= (PONG.height-self.bar.ancho):
                if self.bar.ballcenterx >=self.bar.barx and self.bar.ballcenterx<=(self.bar.barx+self.bar.largo):
                    self.bar.ballvely= -self.bar.ballvely
            #si toca la pared izquierda rebota a la derecha
            if self.bar.ballcenterx >= PONG.width or self.bar.ballcenterx - self.bar.radio<=0:
                self.bar.ballvelx =-self.bar.ballvelx
            
            if self.bar.ballcentery<=0:
                self.bar.ballvely=-self.bar.ballvely
            
            if self.bar.ballcentery>PONG.width:
                terminarjuego=True 
            
            if teclas[pygame.K_LEFT]:
                if self.bar.barx!=0:
                    self.bar.barx-=10
                    self.bar.centrox-=10
            if teclas[pygame.K_RIGHT]:
                if self.bar.barx!=(PONG.width-self.bar.largo):
                    self.bar.barx+=10
                    self.bar.centrox+=10
            
            
            if self.bar.barx!=(PONG.width-self.bar.largo) or  self.bar.barx!=0:
                self.bar.bar2x=self.bar.ballcenterx-(self.bar.largo/2)
        

            self.bar.showBar2(self.bar.bar2x, self.bar.bar2y)
            self.bar.showBar(self.bar.barx,self.bar.bary)
            self.bar.showBall(self.bar.ballcenterx, self.bar.ballcentery)
            pygame.display.update()
            self.gameDisplay.fill(PONG.black)
            self.clock.tick(30)
        pygame.quit()
        quit()

                



    

class Bar:
    def __init__(self):
        self.largo=120
        self.ancho= 16
        self.barx = (PONG.width-self.largo)/2
        self.bary = PONG.height - self.ancho
        self.centrox= (PONG.width/2)
        self.centroy= PONG.height-(self.ancho/2)
        self.radio=15
        self.ballx= self.centrox
        self.bally= self.barx+(self.largo)/2-(2*self.radio)
        self.ballcenterx=100
        self.ballcentery=100
        self.ballvelx=10
        self.ballvely=10
        self.barvel=0
        self.bar2x =(PONG.width-self.largo)/2
        self.bar2y=0
        self.bar2vel=0
    def showBar(self,x,y):
        pygame.draw.rect(PONG.gameDisplay,PONG.white,[x,y,self.largo, self.ancho])
    def showBar2(self,x,y):
        pygame.draw.rect(PONG.gameDisplay,PONG.white,[x,y,self.largo, self.ancho])
    def showBall(self,x,y):
        pygame.draw.circle(PONG.gameDisplay,PONG.white,(int(x),int(y)),self.radio)

        

if __name__ == '__main__':
    game = PONG()