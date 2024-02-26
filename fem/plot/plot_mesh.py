import numpy as np
from matplotlib import pyplot as plt


def plot_mesh(x: np.ndarray, y: np.ndarray, elems_to_nodes: np.ndarray, xlabel='$x$ (m)', ylabel='$y$ (m)', title=''):
    """Plots the given ``msh`` as a ``triplot``."""

    plt.triplot(x, y, elems_to_nodes)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.title(title)
    plt.axis('scaled')
    plt.show()


if __name__ == '__main__':
    # TODO: Dont hardcode values but parse instead
    x = np.array([0, 1, 0, 1])
    y = np.array([0, 0, 1, 1])
    tri = np.array([[0, 1, 2], [1, 2, 3]])
    plot_mesh(x, y, tri)
