from manim import (
    Scene, utils,  # Window
    Circle, Square, Dot,  # Shapes
    Tex,  # Text
    FadeOut, Transform, Create, FadeIn,  # Animations
    ComplexValueTracker, Difference,  # Utils
    ORIGIN, WHITE, GREEN, RIGHT, LEFT, UP, DOWN  # Constants
)
from math import sqrt, pow


def radius(p1, p2):
    return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2)) / 2


def midpoint(p1, p2):
    return [(p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2, 0.0]


def points_to_circle(p1, p2):
    return Circle(
        radius=radius(p1.get_center(), p2.get_center()),
        arc_center=midpoint(p1.get_center(), p2.get_center()),
        color=WHITE,
        # fill_opacity=0.25,
    )


class SomeOffSquare(Scene):
    def make_config(self, p1_coords, p2_coords, square=None, circle=False):
        p1 = Dot(p1_coords)
        p2 = Dot(p2_coords)
        if circle and square:
            circle = points_to_circle(p1, p2)
            off_square = Difference(
                    circle, square, color=GREEN, fill_opacity=0.5)
            self.play(FadeIn(p1), FadeIn(p2), Create(circle),
                      FadeIn(off_square))
            self.wait(0.5)
            self.play(FadeOut(p1), FadeOut(p2), FadeOut(circle),
                      FadeOut(off_square))
            return p1, p2, circle, off_square
        else:
            self.play(FadeIn(p1), FadeIn(p2))
            self.wait(0.3)
            self.play(FadeOut(p1), FadeOut(p2))
            return p1, p2

    def construct(self):
        self.wait(2.0)
        square = Square(5.0)
        self.play(Create(square))
        self.wait(2.0)

        self.make_config(
            [0.3, -0.2, 0.0], [1.0, 0.1, 0.0]
        )
        self.make_config(
            [-1.2, 2.0, 0.0], [-0.3, 0.0, 0.0]
        )
        self.make_config(
            [0.1, -0.1, 0.0], [-0.8, -0.9, 0.0]
        )
        self.make_config(
            [0.0, 2.3, 0.0], [-0.2, -0.4, 0.0], square, True
        )
        self.make_config(
            [0.7, 0.8, 0.0], [-0.3, -0.4, 0.0], square, True
        )
        self.make_config(
            [-0.3, -1.2, 0.0], [2.0, 0.0, 0.0], square, True
        )
        self.make_config(
            [-0.1, 0.6, 0.0], [-2.9, -0.8, 0.0], square, True
        )

        p1 = Dot([2.1, -0.5, 0.0])
        p2 = Dot([0.3, -0.4, 0.0])
        circle = points_to_circle(p1, p2)
        off_square = Difference(
                circle, square, color=GREEN, fill_opacity=0.5)
        self.play(FadeIn(p1), FadeIn(p2), Create(circle),
                  FadeIn(off_square))
        self.wait(0.5)

        self.play(p1.shift(LEFT))
