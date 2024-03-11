from manim import (
    Scene, utils,  # Window
    Circle, Square, Dot,  # Shapes
    Tex,  # Text
    FadeIn,  # Animations
    ComplexValueTracker, Difference,  # Utils
    ORIGIN, WHITE  # Constants
)
from math import sqrt, pow

PURPLE = utils.color.X11.MEDIUMSLATEBLUE


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
    def construct(self):
        tex = Tex(r"\LaTeX", font_size=144)
        self.add(tex)

        # Set up square, points, circle
        square = Square(5.0)
        p1, p2 = Dot(ORIGIN), Dot([0.0, 1.0, 0.0])
        circle = points_to_circle(p1, p2)
        off_square = Difference(circle, square, color=PURPLE, fill_opacity=0.5)
        p1_tracker = ComplexValueTracker(0 + 0j)
        p2_tracker = ComplexValueTracker(0 + 0j)
        p1.add_updater(lambda z: z.move_to(p1_tracker.points))
        p2.add_updater(lambda z: z.move_to(p2_tracker.points))
        circle.add_updater(lambda z: z.become(points_to_circle(p1, p2)))
        off_square.add_updater(lambda z: z.become(
            Difference(circle, square, color=PURPLE,
                       fill_opacity=0.5)))
        self.play(FadeIn(square), FadeIn(p1), FadeIn(p2), FadeIn(circle))
        self.add(off_square)

        # Move the points around
        points = [
            (p1_tracker, (1 + 0j)),
            (p2_tracker, (5/2 + 2j)),
            (p2_tracker, (-2/5 + 2j)),
            (p1_tracker, (-2/5 + 5/2j)),
            (p2_tracker, (7/3 + -5/3j)),
            (p1_tracker, (1/2 + -5/2j)),
            (p2_tracker, (-2/5 + 2j)),
            (p1_tracker, (-2/5 + -2j)),
            (p2_tracker, (2 + 1/2j)),
        ]
        for tracker, point in points:
            self.play(tracker.animate.set_value(point))
            self.wait(0.75)

        # Slide over
        self.play(
            square.animate.shift([-2, 0, 0]),
            p1_tracker.animate.set_value(
                -2.4 - 2j
            ),
            p2_tracker.animate.set_value(
                0 - 0.5j
            )
        )
