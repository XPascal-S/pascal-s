import matplotlib.pyplot as plt
import networkx as nx
from networkx.drawing.nx_agraph import graphviz_layout

import py_ast

# import pygraphviz as pgv


labels = {}
sizes = {}


def travel_tree(ast_g, node: py_ast.Node, dep):
    ast_g.add_node(node)
    sizes[node] = 1000 / dep
    if not node.children:
        labels[node] = node.GetTokenSymbol()
    else:
        labels[node] = node.type.name
    for c in node.children:
        ast_g.add_edge(node, c)
        travel_tree(ast_g, c, dep+1)


G = nx.DiGraph()
ast_root = py_ast.ParseToken()
travel_tree(G, ast_root, 1)
pos = graphviz_layout(G, prog='dot')
plt.figure(figsize=(16, 9))
nx.draw(G, pos, alpha=0.5, node_sizes=sizes, arrows=True)
nx.draw_networkx_labels(G, pos, labels)
plt.show()
