from manim import *
from lib.array import get_1d_array

SVG_PATH = "C:\\Users\\Phon1209\\Desktop\\Work\\posn-tutorial\\manim_video\\programming.in.th\\assets\\svg"


class Array1D(Scene):
    def construct(self):
        arr = get_1d_array(13, values=[i for i in range(1, 14)])
        arr.arrange_in_grid(rows=1, buff=0)
        self.play(Create(arr))
        self.wait()

        # highlight all element in bad array
        red_cell = [3, 4, 7, 10, 12]
        self.play(*[(arr[i - 1][0].animate.set_color(RED).set_opacity(0.6))
                  for i in red_cell], run_time=2)
        self.wait()

        # Put first cover
        left_point = arr[red_cell[0] - 1].get_corner(UL)
        right_point = arr[red_cell[-1] - 1].get_corner(UR)
        cover = Line(start=left_point,
                     end=right_point,
                     color=GREEN,
                     stroke_width=8,
                     buff=0).shift(UP * 0.2)

        self.play(FadeIn(cover), run_time=2)
        self.wait()

        # Extend cover
        self.play(cover.animate.put_start_and_end_on(arr[0].get_corner(UL),
                                                     arr[red_cell[-1] - 1].get_corner(UR)).shift(UP * 0.2))
        self.wait(2)
        self.play(cover.animate.put_start_and_end_on(
            arr[red_cell[0] - 1].get_corner(UL), arr[red_cell[-1] - 1].get_corner(UR)).shift(UP * 0.2))
        self.wait()

        # left and right
        left_text = MathTex(r"\text{left}").next_to(arr[red_cell[0] - 1], DOWN)
        right_text = MathTex(r"\text{right}").next_to(
            arr[red_cell[-1] - 1], DOWN)
        self.play(Create(left_text), Create(right_text))
        self.wait()

        # Add Brace
        total_brace = BraceBetweenPoints(
            arr[red_cell[0] - 1].get_corner(DL), arr[red_cell[-1] - 1].get_corner(DR))
        total_eq = MathTex(r"\text{total} = \text{right} - \text{left} + 1").next_to(
            total_brace, DOWN)
        self.play(FadeOut(left_text), FadeOut(right_text))
        # self.wait()
        self.play(FadeIn(total_brace), FadeIn(total_eq))
        self.wait()

        # Add red blob
        red_text = MathTex(r"m \text{ bad blocks}").next_to(
            total_brace, DOWN)
        final_eq = MathTex(
            r"\text{covered} = \text{total} - m").next_to(total_brace, DOWN)
        self.play(FadeOut(total_eq), FadeIn(red_text))
        self.wait(2)

        self.play(TransformMatchingTex(red_text, final_eq))
        self.wait(2)

        with_number = MathTex(
            r"\text{covered} = 12 - 3 + 1 - 5 = 5").next_to(total_brace, DOWN)
        self.play(TransformMatchingTex(final_eq, with_number))
        self.wait(2)

        # Remove all explanation
        self.play(FadeOut(with_number), FadeOut(total_brace))
        self.wait(2)

        # Duplicate the cover
        cover_copy = cover.copy()
        self.play(cover.animate.put_start_and_end_on(
            arr[red_cell[0] - 1].get_corner(UL),
            arr[7].get_corner(UR)
        ).shift(UP * 0.2 + LEFT*0.1),
            cover_copy.animate.put_start_and_end_on(
            arr[8].get_corner(UL),
            arr[red_cell[-1] - 1].get_corner(UR))
            .shift(UP * 0.2 + RIGHT * 0.1).set_color(BLUE))
        self.wait()

        # Shrink the cover
        self.play(cover.animate.put_start_and_end_on(
            arr[red_cell[0] - 1].get_corner(UL),
            arr[red_cell[2] - 1].get_corner(UR)
        ).shift(UP * 0.2).set_color(BLUE),
            cover_copy.animate.put_start_and_end_on(
            arr[red_cell[3] - 1].get_corner(UL),
            arr[red_cell[-1] - 1].get_corner(UR))
            .shift(UP * 0.2))

        bi = BraceBetweenPoints(
            arr[red_cell[2] - 1].get_corner(DR), arr[red_cell[3] - 1].get_corner(DL))
        bi_text = MathTex(r"2").next_to(bi, DOWN)
        self.play(FadeIn(bi), FadeIn(bi_text))
        self.wait()

        # Reset the cover
        self.play(FadeOut(bi), FadeOut(bi_text))
        self.play(cover.animate.put_start_and_end_on(arr[red_cell[0] - 1].get_corner(UL),
                                                     arr[red_cell[-1] - 1].get_corner(UR)).shift(UP * 0.2).set_color(GREEN),
                  FadeOut(cover_copy))
        self.wait()

        # Slice at the wrong place
        cover_copy = cover.copy()
        self.play(cover.animate.put_start_and_end_on(
            arr[red_cell[0] - 1].get_corner(UL),
            arr[2].get_corner(UR)
        ).shift(UP * 0.2 + LEFT*0.05),
            cover_copy.animate.put_start_and_end_on(
            arr[3].get_corner(UL),
            arr[red_cell[-1] - 1].get_corner(UR))
            .shift(UP * 0.2 + RIGHT * 0.05).set_color(BLUE))

        bi_text = MathTex(r"0").next_to(arr[2].get_corner(DR), DOWN)
        self.play(FadeIn(bi_text))
        self.wait()

        # Reset the cover
        self.play(FadeOut(bi_text))
        self.play(cover.animate.put_start_and_end_on(arr[red_cell[0] - 1].get_corner(UL),
                                                     arr[red_cell[-1] - 1].get_corner(UR)).shift(UP * 0.2).set_color(GREEN),
                  FadeOut(cover_copy))
        self.wait()

        # Show the slicable piece
        # enumerate all possible slice
        brace_group = VGroup()
        gap = []
        for i, j in zip(red_cell, red_cell[1:]):
            if j - i == 1:
                continue
            brac = BraceBetweenPoints(
                arr[i - 1].get_corner(DR), arr[j - 1].get_corner(DL))
            strin = str(j - i - 1)
            brac_text = MathTex(strin).next_to(brac, DOWN)
            gr = VGroup(brac, brac_text)
            brace_group.add(gr)
            gap.append((i - 1, j - 1))
        self.play(FadeIn(brace_group))
        self.wait()

        # Highlight the sliceable piece

        for i, r in zip(brace_group, gap):
            self.play(i[0].animate.set_color(BLUE),
                      i[1].animate.set_color(BLUE))
            self.wait()
            cover_copy = cover.copy()
            self.play(cover_copy.animate.put_start_and_end_on(
                cover_copy.get_start(),
                arr[r[0]].get_corner(UR) + [0, 0.2, 0],
            ),
                cover.animate.put_start_and_end_on(
                arr[r[1]].get_corner(UL) + [0, 0.2, 0],
                cover.get_end()))
            self.play(FadeOut(i))


class Test(Scene):
    def construct(self):
        print(UP, DOWN, LEFT, RIGHT)
