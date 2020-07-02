import math

import matplotlib.pyplot as plt
import networkx as nx
from networkx.drawing.nx_agraph import graphviz_layout

import py_ast

# import pygraphviz as pgv


labels = {}
sizes = {}


def travel_tree(ast_g, node: py_ast.Node, dep):
    if node.type == py_ast.Type.ExpVoid:
        return
    ast_g.add_node(node)
    sizes[node] = 1000 / (math.log10(dep) + 1)
    if not node.children:
        labels[node] = node.GetTokenSymbol()
    else:
        labels[node] = node.type.name
    for c in node.children:
        if not c.type == py_ast.Type.ExpVoid:
            ast_g.add_edge(node, c)
            travel_tree(ast_g, c, dep+1)


G = nx.DiGraph()
ast_root = py_ast.ParseToken()
travel_tree(G, ast_root, 1)
pos = graphviz_layout(G, prog='dot')
plt.figure(figsize=(16, 9))
nx.draw(G, pos, alpha=0.3, node_size=list(
    sizes.values()), arrows=True, node_shape='o')
nx.draw_networkx_labels(
    G, dict(map(lambda x: (x[0], (x[1][0], x[1][1]-15)), pos.items())), labels)
plt.show()
