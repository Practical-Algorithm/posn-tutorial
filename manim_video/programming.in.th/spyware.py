from manim import *

SVG_PATH = "C:\\Users\\Phon1209\\Desktop\\Work\\posn-tutorial\\manim_video\\programming.in.th\\assets\\svg"


class MainScene(Scene):
    def construct(self):
        # Graph value
        vertices = [i for i in range(1, 6)]
        edges = [(1, 2), (2, 4), (1, 3), (1, 4), (4, 5)]
        values = [5, 8, 2, 10, 7]
        starting_red_vertex = 2

        def getValue(v):
            return values[v - 1]

        # Draw a graph
        g = Graph(vertices, edges, labels=True,
                  layout="spring", layout_scale=2.5, vertex_config={
                      'radius': 0.4,
                  })
        self.play(Create(g))
        self.wait()

        # Add values to each node
        valueTexts = VGroup()
        for i in range(1, 6):
            value_text = MathTex(getValue(i)).scale(
                0.6).next_to(g.vertices[i], LEFT)
            valueTexts.add(value_text)

        self.play(FadeIn(valueTexts))

        # Add spyware
        self.play(g.vertices[starting_red_vertex].animate.set_color(
            RED), FadeOut(valueTexts[starting_red_vertex - 1]))
        self.wait()

        # breath first search

        # bfs_queue = [spyware]

        # labeling the depth of each node
        # change the color of the node based on the depth

        # Method 1: select from each depth iteratively

        # Method 2: select from the most valuable available node

        # Method 3: (correct) select backward from the most valuable node

        pass
