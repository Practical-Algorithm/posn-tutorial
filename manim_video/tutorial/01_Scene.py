from manim import *

# Use command below to run this script
# manim 01_Scene.py Scene1 -pql
# -p: Preview the animation
# -q: Render in low quality
# -ql: Render in low quality
# -m: Render in medium quality
# -h: Render in high quality
# -k: Keep the intermediate files
# -s: Save the screenshot of the final frame
# Scene1: Class name of the scene to be rendered


# Create a class that inherits from Scene
# This class will be the first scene in the video
class Scene1(Scene):
    def construct(self):
        # Create an object here

        sq = Square(
            side_length=2,
            color=BLUE,
            fill_color=BLUE,
            fill_opacity=0.5
        )

        self.play(Create(sq))
        self.wait()


class Getters(Scene):
    def construct(self):
        rect = Rectangle(
            width=2,
            height=3,
            color=RED,
        ).to_edge(UL)

        circ = Circle(
            radius=1,
            color=GREEN,
        ).to_corner(DL)

        arrow = always_redraw(lambda: Arrow(
            start=rect.get_center(),
            end=circ.get_center(),
            color=WHITE,
        ))

        # Add objects to the scene instantly
        self.add(rect, circ, arrow)

        # Create in sequence
        # self.play(Create(VGroup(rect, circ, arrow)))

        # Create in parallel
        # self.play(Create(rect), Create(circ), Create(arrow))
        self.wait()

        # Move the objects in parallel
        self.play(rect.animate.to_edge(DR), circ.animate.to_corner(UR), run_time=3)\

        # Move the objects in sequence
        # self.play(rect.animate.to_edge(DR), run_time=3)
        # self.play(circ.animate.to_corner(UR), run_time=3)
        self.wait()


class MobjectArray(Scene):
    def construct(self):
        arr = [Square(), Circle(), Triangle()]
        self.play(Create(VGroup(*arr)))
        self.wait()


class Updater(Scene):
    def construct(self):
        dot = Dot()
        text = Text("ln(2)").next_to(dot, UP)
        self.add(dot, text)

        # Update the position of the text
        text.add_updater(lambda m: m.next_to(dot, UP))
        self.play(dot.animate.to_edge(DOWN), run_time=3)
        self.wait()

        # Remove the updater
        text.clear_updaters()
        self.play(dot.animate.to_edge(UP), run_time=3)
        self.wait()


class ValueTracker1(Scene):
    def construct(self):
        vt = ValueTracker(0)

        # or use always_redraw
        num = DecimalNumber(vt.get_value()).add_updater(
            lambda v: v.set_value(vt.get_value()))
        self.add(num)
        self.wait()

        self.play(vt.animate.set_value(10), run_time=3)
        self.wait()


class Array1D(Scene):

    def get_grid_box(self, value, stroke_width=2, color=WHITE):
        return VGroup(
            MathTex("{:.0f}".format(value)),
            Square(side_length=.5, color=color, stroke_width=stroke_width)
        )

    def construct(self):
        arr = [1, 2, 3, 4, 5]
        arr_group = VGroup(*[self.get_grid_box(i) for i in arr]).arrange(RIGHT)
        self.play(Create(arr_group))
        self.wait()
