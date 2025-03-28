
def read_input():
    inp = input().split(" ")
    name = inp[0]
    value = int(inp[1])

    return name, value


def read_connection():
    inp = input().split(" ")
    # print(inp)
    n1 = inp[0].strip()
    op = inp[1].strip()
    n2 = inp[2].strip()
    out = inp[4].strip()

    return n1, op, n2, out


class Wire:
    def __init__(self, name):
        self.name = name
        self.value = None
        self.connections = list()
        self.valFrom = list()
        self.indeg = 0
        self.op = None

    def setValue(self, value):
        self.value = value

    def addConnection(self, other):
        self.connections.append(other.name)
        other.valFrom.append(self.name)
        other.indeg += 1

    def setOp(self, op):
        self.op = op

    def __str__(self):
        return f"{self.name}: {self.value}"


mapping = dict()


def test(fix_index):
    fix = "{:02d}".format(fix_index)
    inc = "{:02d}".format(fix_index + 1)

    # Reset
    for wire in mapping.values():
        if wire.name[0] == 'x' or wire.name[0] == 'y':
            wire.setValue(0)
        else:
            wire.setValue(None)
            wire.indeg = 2

    mapping['x' + fix].setValue(1)
    mapping['y' + fix].setValue(1)

    queue = list()
    for wire in mapping.values():
        if wire.indeg == 0:
            queue.append(wire)

    while len(queue) != 0:
        wire = queue.pop(0)
        if wire.value is None:
            if wire.op == "AND":
                wire.setValue(mapping[wire.valFrom[0]].value &
                              mapping[wire.valFrom[1]].value)
            elif wire.op == "OR":
                wire.setValue(mapping[wire.valFrom[0]].value |
                              mapping[wire.valFrom[1]].value)

            elif wire.op == "XOR":
                wire.setValue(mapping[wire.valFrom[0]].value ^
                              mapping[wire.valFrom[1]].value)
            # print(wire.name, wire.op, wire.valFrom,
            #       mapping[wire.valFrom[0]].value, mapping[wire.valFrom[1]].value,
            #       wire.value)
        # else:
            # print(wire.name, wire.value)

        for conn in wire.connections:
            nextWire = mapping[conn]
            nextWire.indeg -= 1
            if nextWire.indeg == 0:
                # print(nextWire.name, nextWire.op, nextWire.valFrom)
                queue.append(nextWire)

    # for wire in mapping.values():
    #     print(wire)

    # z wire
    answer = 0
    for i in ['z' + "{:02d}".format(i) for i in range(45, -1, -1)]:
        # print(mapping[i])
        answer *= 2
        answer += mapping[i].value

        if i == ('z' + inc) and mapping[i].value == 0:
            print("Something is bad at", fix_index, i, mapping[i].value)

    # print(answer)
    return answer


def main():
    for _ in range(90):
        name, _ = read_input()
        mapping[name] = Wire(name)
        mapping[name].setValue(0)

    for _ in range(222):
        n1, op, n2, out = read_connection()
        if n1 not in mapping:
            mapping[n1] = Wire(n1)
        if n2 not in mapping:
            mapping[n2] = Wire(n2)
        if out not in mapping:
            mapping[out] = Wire(out)

        n1 = mapping[n1]
        n2 = mapping[n2]
        out = mapping[out]

        n1.addConnection(out)
        n2.addConnection(out)
        out.setOp(op)

    for i in range(45):
        expect = (1 << (i+1))
        got = test(i)

        if expect != got:
            print(f"Test {i} failed: expected {expect} got {got}")


if __name__ == "__main__":
    main()
