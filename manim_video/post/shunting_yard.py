from manim import *
from lib.array import get_1d_array

# Animation for Shunting Yard algorithm


class MainScene(Scene):
    def construct(self):
        # expression = "3 + 4 * 2 / ( 1 - 5 )"
        expression = "3 * 4 + 2 / ( 1 - 2 )"
        splited_expression = expression.split()

        arr = get_1d_array(len(splited_expression),
                           values=splited_expression, stroke_width=1, buff=0).to_corner(UR, buff=1)

        stack = []
        queue = []
        operators = ['+', '-', '*', '/']
        operatorPrecedence = {
            '+': 1,
            '-': 1,
            '*': 2,
            '/': 2
        }
        expr_buff = 0.4

        # Init the scene
        expr = MathTex(expression).scale(1.5)

        # Create a box without top for stack
        stack_box = Rectangle(
            width=1, height=5, color=BLUE).shift(LEFT * 4)
        stack_text = Text("Stack").next_to(stack_box, UP)
        expr.next_to(stack_box, RIGHT, buff=1).shift(UP * 2)

        # Output Text
        output_text = Text("Output:").next_to(
            stack_box, RIGHT, buff=1).shift(UP)

        initScene = VGroup(expr, stack_box, stack_text, output_text)
        initAnimation = [
            FadeIn(expr),
            FadeIn(stack_box),
            Write(stack_text),
            Write(output_text)
        ]
        self.play(AnimationGroup(*initAnimation, lag_ratio=0.1))
        self.wait(5)

        # Track the location of output and stack
        expr_location = output_text
        stack_location = stack_box.get_bottom()

        # Shunting Yard algorithm
        for token, index in zip(splited_expression, range(len(splited_expression))):

            self.play(expr[0][index].animate.set_color(YELLOW))
            self.wait(5)

            if token.isnumeric():
                # Play "" is number
                self.play(expr[0][index].animate.set_color(GREEN_B))
                self.wait(5)
                # Move to output (WIP)
                self.play(expr[0][index].animate.next_to(
                    expr_location, RIGHT, buff=expr_buff))
                self.wait(5)
                expr_location = expr[0][index]
                queue.append(token)
            elif token in operators:
                self.play(expr[0][index].animate.set_color(BLUE))
                self.wait(5)
                while stack and stack[-1][0] in operators and operatorPrecedence[stack[-1][0]] >= operatorPrecedence[token]:
                    op, ind = stack.pop()
                    # Move up and fade out
                    self.play(expr[0][ind].animate.set_opacity(
                        0).shift(UP * 0.5))
                    self.wait(5)
                    copy_op = expr[0][ind].copy()
                    copy_op.set_opacity(1)
                    copy_op.next_to(expr_location, RIGHT,
                                    buff=expr_buff).shift(UP * 0.5)
                    self.play(copy_op.animate.next_to(
                        expr_location, RIGHT, buff=expr_buff))
                    self.wait(5)
                    expr_location = copy_op

                    queue.append(op)
                if stack:
                    stack_location = expr[0][stack[-1][1]]
                else:
                    stack_location = stack_box.get_bottom()

                # Move to stack (WIP)
                self.play(expr[0][index].animate.next_to(
                    stack_location, UP, buff=expr_buff))
                self.wait(5)
                stack_location = expr[0][index]
                stack.append((token, index))
            elif token == '(':
                self.play(expr[0][index].animate.set_color(BLUE))
                self.wait(5)
                # Move to stack (WIP)
                self.play(expr[0][index].animate.next_to(
                    stack_location, UP, buff=expr_buff))
                self.wait(5)
                stack_location = expr[0][index]
                stack.append((token, index))
            elif token == ')':
                while stack and stack[-1][0] != '(':
                    op, ind = stack.pop()
                    # Move up and fade out
                    self.play(expr[0][ind].animate.set_opacity(
                        0).shift(UP * 0.5))
                    self.wait(5)

                    copy_op = expr[0][ind].copy()
                    copy_op
                    copy_op.next_to(expr_location, RIGHT,
                                    buff=expr_buff).shift(UP * 0.5)
                    self.play(copy_op.animate.next_to(
                        expr_location, RIGHT, buff=expr_buff).set_opacity(1))
                    self.wait(5)
                    expr_location = copy_op

                    queue.append(op)

                op, ind = stack.pop()
                # Move up and fade out
                self.play(expr[0][ind].animate.set_opacity(
                    0).shift(UP * 0.5))
                self.wait(5)
                if len(stack) > 0:
                    stack_location = expr[0][stack[-1][1]]
                else:
                    stack_location = stack_box.get_bottom()

                # Fade out the bracket
                self.play(expr[0][index].animate.set_opacity(0))
                self.wait(5)

        while stack:
            op, ind = stack.pop()
            # Move up and fade out
            self.play(expr[0][ind].animate.set_opacity(
                0).shift(UP * 0.5))
            self.wait(5)

            copy_op = expr[0][ind].copy()
            copy_op.next_to(expr_location, RIGHT,
                            buff=expr_buff).shift(UP * 0.5)
            self.play(copy_op.animate.next_to(
                expr_location, RIGHT, buff=expr_buff).set_opacity(1))
            self.wait(5)
            expr_location = copy_op
            queue.append(op)
        self.wait()


class Evaluate(Scene):
    def construct(self):
        postfix = "3 4 * 2 1 2 - / +"

        stack = []
        operators = ['+', '-', '*', '/']
        expr_buff = 0.4
        dictMobj = {}

        sliced_postfix = postfix.split()
        arr = get_1d_array(len(sliced_postfix),
                           values=sliced_postfix, stroke_width=1, buff=0).to_corner(UR, buff=1)
        mobjIndex = len(sliced_postfix) + 1

        # Create a box without top for stack
        stack_box = Rectangle(
            width=2, height=5, color=BLUE).to_corner(DL, buff=1)
        stack_text = Text("Stack").next_to(stack_box, UP)

        self.play(AnimationGroup(FadeIn(arr), FadeIn(stack_box),
                                 Write(stack_text)))
        self.wait(5)

        stack_location = stack_box.get_bottom()

        def getMobj(index):
            if index in dictMobj:
                return dictMobj[index]
            else:
                return arr[index]

        def MoveToStack(index, stack_location):
            if index in dictMobj:
                self.play(getMobj(index).animate.next_to(
                    stack_location, UP, buff=expr_buff))
                self.wait(5)
            else:
                obj = getMobj(index)
                self.play(obj[1].animate.next_to(
                    stack_location, UP, buff=expr_buff),
                    FadeOut(obj[0]))
                self.wait(5)
                dictMobj[index] = obj[1]
            return getMobj(index)

        for token, index in zip(sliced_postfix, range(len(sliced_postfix))):
            if token.isnumeric():

                self.play(getMobj(index).animate.set_color(GREEN_B))
                self.wait(5)
                stack_location = MoveToStack(index, stack_location)
                stack.append((token, index))
            elif token in operators:
                self.play(getMobj(index).animate.set_color(BLUE))
                self.wait(5)
                op = getMobj(index)
                self.play(op[1].animate.center(), FadeOut(op[0]))
                self.wait(5)
                num2, index2 = stack.pop()
                self.play(getMobj(index2).animate.next_to(
                    op[1], RIGHT, buff=expr_buff
                ))
                self.wait(5)
                num1, index1 = stack.pop()
                self.play(getMobj(index1).animate.next_to(
                    op[1], LEFT, buff=expr_buff
                ))
                self.wait(5)
                exp = f"{num1} {token} {num2}"
                result = int(eval(exp))
                e2 = MathTex(result).scale(1.5).set_color(GREEN_B)
                anim = [
                    FadeOut(getMobj(index1)),
                    FadeOut(op[1]),
                    FadeOut(getMobj(index2)),
                    Write(e2)
                ]
                self.play(AnimationGroup(*anim, lag_ratio=0))
                self.wait(5)

                dictMobj[mobjIndex] = e2
                if len(stack) > 0:
                    stack_location = getMobj(stack[-1][1])
                else:
                    stack_location = stack_box.get_bottom()

                stack.append((result, mobjIndex))
                mobjIndex += 1
                stack_location = MoveToStack(mobjIndex - 1, stack_location)
            self.wait(0.2)

        ans = Text("Answer: ")
        st = stack.pop()[1]
        self.play(Write(ans), getMobj(st).animate.next_to(ans, RIGHT))
        self.wait()
