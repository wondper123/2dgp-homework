from pico2d import *
import gfw
from gobj import *

class LaserBullet:
    SIZE = 40
    def __init__(self, x, y, speed):
        # self.pos = get_canvas_width() // 2, get_canvas_height() // 2
        self.x, self.y = x, y
        self.dy = speed
        self.image = gfw.image.load(RES_DIR + '/plane1_bullet.png')
        self.power = 100
        self.image.w = 35
        self.image.h = 40

    def draw(self):
        self.image.clip_draw(2,0, self.image.w, self.image.h, self.x, self.y)

    def update(self):
        self.y += self.dy * gfw.delta_time

        if self.y > get_canvas_height() + LaserBullet.SIZE:
            self.remove()

    def remove(self):
        gfw.world.remove(self)

    def get_bb(self):
        hw = self.image.w // 2
        hh = self.image.h // 2
        return self.x - hw, self.y - hh, self.x + hw, self.y + hh

class EnemyBullet:#총알 이미지 바꾸고 점점 내려오도록 그리고 remove설정
    SIZE = 19
    turn = 0
    def __init__(self, x, y, speed):
        # self.pos = get_canvas_width() // 2, get_canvas_height() // 2
        self.x, self.y = x, y
        self.dy = speed
        self.image = gfw.image.load(RES_DIR + '/enemy_bullet.png')
        self.power = 100
        self.image.w = 20
        self.image.h = 19

    def draw(self):
        self.image.clip_draw(2,0, self.image.w, self.image.h, self.x+(self.image.w*EnemyBullet.turn), self.y)

    def update(self):
        self.y -= self.dy * gfw.delta_time

        if EnemyBullet.turn==0:
            EnemyBullet.turn = 1
        else:
            EnemyBullet.turn = 0
        if self.y < 0 - EnemyBullet.SIZE:
            self.remove()

    def remove(self):
        gfw.world.remove(self)

    def get_bb(self):
        hw = self.image.w // 2
        hh = self.image.h // 2
        return self.x - hw, self.y - hh, self.x + hw, self.y + hh