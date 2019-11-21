import pickle
import random

import pygame
import math

from pygame import font


import numpy as np


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
        puntos=0
        font = pygame.font.SysFont(None,25)
        while not terminarjuego:
            for evento in pygame.event.get():
                if evento.type == pygame.QUIT:
                    terminarjuego==True
            teclas= pygame.key.get_pressed()
            self.bar.ballcenterx+=self.bar.ballvelx
            self.bar.ballcentery+=self.bar.ballvely
            msg = 'Puntuacion: ' + str(puntos)
            screen_text = font.render(msg,True,(255,255,255))
            self.gameDisplay.blit(screen_text,[10,300])           
            
            #si toca el techo, rebota hacia abajo
            if self.bar.ChoqueBarra():
                self.bar.ballvely= -self.bar.ballvely
                puntos+=1
                self.bar.ballcenterx+=10
            #si toca la pared izquierda rebota a la derecha
            if self.bar.Choquederecha():
                self.bar.ballvelx =-self.bar.ballvelx
            
            if self.bar.ChoqueArriba():
                self.bar.ballvely=-self.bar.ballvely
            
            if self.bar.ChoqueAbajo():
                terminarjuego=True 
            
            if teclas[pygame.K_LEFT]:
                self.bar.MoverIzquierda()
            if teclas[pygame.K_RIGHT]:
                self.bar.Moverderecha()
            
            
            if self.bar.barx!=(PONG.width-self.bar.largo) or  self.bar.barx!=0:
                self.bar.bar2x=self.bar.ballcenterx-(self.bar.largo/2)
        
            print(self.bar.ballcentery, self.bar.ballcentery+self.bar.radio)
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
    def ChoqueBarra(self):
        if (self.ballcentery+self.radio)>= (PONG.height-self.ancho):
                if self.ballcenterx >=self.barx and self.ballcenterx<=(self.barx+self.largo):
                    return True
    def Choquederecha(self):
        if self.ballcenterx >= PONG.width or self.ballcenterx - self.radio<=0:
            return True
    def ChoqueArriba(self):
        if self.ballcentery<=self.ancho:
            return True
    def ChoqueAbajo(self):
        if self.ballcentery+self.radio>PONG.height:
             return True
    def MoverIzquierda(self):
        if self.barx!=0:
            self.barx-=10
            self.centrox-=10
    def Moverderecha(self):
        if self.barx!=(PONG.width-self.largo):
            self.barx+=10
            self.centrox+=10
        



        

if __name__ == '__main__':
    game = PONG()