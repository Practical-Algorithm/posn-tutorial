from manim import *
from lib import array

wait_time = 2


class Stack(Scene):
    def w(self):
        self.wait(wait_time)

    def construct(self):
        # box size varied big -> small
        base = Rectangle(width=4, height=1, color=GREEN).to_edge(DOWN)
        middle = Rectangle(width=3, height=1, color=YELLOW)
        top = Rectangle(width=2, height=1, color=BLUE)

        self.play(Create(base))
        self.w()

        self.play(Create(middle))
        self.play(middle.animate.next_to(base, UP))
        self.w()

        self.play(Create(top))
        self.play(top.animate.next_to(middle, UP))
        self.w()
        # removing boxes - remove from top

        self.play(top.animate.shift(UP * 1.5).set_opacity(0))
        self.play(middle.animate.shift(UP * 1.5).set_opacity(0))
        self.w()

        # randomly sized box
        middle.next_to(base, UP)
        top.next_to(middle, UP)

        self.play(middle.animate.set_opacity(1),
                  top.animate.set_opacity(1),
                  base.animate.set_opacity(1))
        self.w()

        self.play(base.animate.stretch_to_fit_width(2),
                  middle.animate.stretch_to_fit_width(1),
                  top.animate.stretch_to_fit_width(3)
                  )
        self.w()

        self.play(base.animate.stretch_to_fit_width(4),
                  middle.animate.stretch_to_fit_width(4),
                  top.animate.stretch_to_fit_width(2)
                  )
        self.w()

        self.play(base.animate.stretch_to_fit_width(1),
                  middle.animate.stretch_to_fit_width(2),
                  top.animate.stretch_to_fit_width(3)
                  )
        self.w()

        # equal sized box
        self.play(base.animate.stretch_to_fit_width(2),
                  middle.animate.stretch_to_fit_width(2),
                  top.animate.stretch_to_fit_width(2)
                  )
        self.w()

        # Change it to number/ blah
        value_top = MathTex(r"1").move_to(top.get_center())
        value_middle = MathTex(r"Hello").move_to(middle.get_center())
        value_base = MathTex(r"False").move_to(base.get_center())
        self.play(base.animate.set_fill(opacity=0),
                  middle.animate.set_fill(opacity=0),
                  top.animate.set_fill(opacity=0)
                  )
        self.play(Write(VGroup(value_top, value_middle, value_base)))
        self.w()

        # Change all to number or something
        value_middle_s = MathTex(r"2").move_to(value_middle.get_center())
        value_base_s = MathTex(r"3").move_to(value_base.get_center())
        self.play(TransformMatchingTex(value_middle, value_middle_s),
                  TransformMatchingTex(value_base, value_base_s),
                  run_time=2
                  )
        self.w()

        value_base_ss = MathTex(r"!").move_to(value_base_s.get_center())
        value_middle_ss = MathTex(r"I").move_to(value_middle_s.get_center())
        value_top_ss = MathTex(r"H").move_to(value_top.get_center())
        self.play(TransformMatchingTex(value_base_s, value_base_ss),
                  TransformMatchingTex(value_middle_s, value_middle_ss),
                  TransformMatchingTex(
                      value_top, value_top_ss),
                  )
        self.w()

        value_base_sss = MathTex(r"Algorithms!").move_to(
            value_base_s.get_center())
        value_middle_sss = MathTex(r"Practical").move_to(
            value_middle_s.get_center())
        value_top_sss = MathTex(r"Like").move_to(value_top.get_center())
        stretch = AnimationGroup(*[
            base.animate.stretch_to_fit_width(4),
            middle.animate.stretch_to_fit_width(4),
            top.animate.stretch_to_fit_width(4)
        ])
        self.play(stretch)
        self.play(TransformMatchingTex(value_base_ss, value_base_sss),
                  TransformMatchingTex(value_middle_ss, value_middle_sss),
                  TransformMatchingTex(
                      value_top_ss, value_top_sss)
                  )
        self.w()


class DS(Scene):
    def w(self):
        self.wait(wait_time)

    def construct(self):
        # Stack box
        box = Rectangle(width=1.5, height=6, color=BLUE).shift(
            LEFT * 3)
        stack_text = Text("Stack").next_to(box, LEFT, buff=0.5).shift(UP * 2.5)
        black_box = Rectangle(
            width=2, height=0.1, color=BLACK).set_fill(BLACK, opacity=1).next_to(box, UP, buff=0)

        self.add(box, stack_text, black_box)

        arr = array.get_1d_array(length=5)

        iarr = arr.copy()

        input_text = Text("Input:").shift(UP * 2)
        iarr.next_to(input_text, RIGHT, buff=0.2)

        # Top, Size, Empty
        sc = 0.5
        top_text = Text("Top: ").scale(sc).shift(UP * 1)
        size_text = Text("Size: ").scale(sc).shift(UP * 0.5)
        empty_text = Text("Empty: ").scale(sc)

        top_vt = ValueTracker(-1)
        size_vt = ValueTracker(0)
        empty_vt = ValueTracker(0)

        self.play(FadeIn(input_text, iarr))
        self.w()

        self.play(FadeIn(VGroup(top_text, size_text, empty_text)))
        self.w()

        stack_location = box.get_bottom()
        for x, y in zip(arr, iarr):

            self.play(y.animate.set_opacity(0))

            x.next_to(stack_location, UP, buff=0.2)
            stack_location = x
            self.play(FadeIn(x))
            self.wait(2)

            # Setting up the DS

        self.w()
