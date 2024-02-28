import gmsh

from gmsh_model import gmsh_model

cad = gmsh.model.occ


@gmsh_model("unit_square", dim=2, finalize=False, options={"Mesh.MeshSizeFactor": 7.5})
def gen_unit_square():
    """Creates a mesh of the unit square."""

    p1 = cad.add_point(0, 0, 0)
    p2 = cad.add_point(0, 1, 0)
    p3 = cad.add_point(1, 1, 0)
    p4 = cad.add_point(1, 0, 0)
    l1 = cad.add_line(p1, p2)
    l2 = cad.add_line(p2, p3)
    l3 = cad.add_line(p3, p4)
    l4 = cad.add_line(p4, p1)
    boundary = cad.add_curve_loop([l1, l2, l3, l4])
    cad.add_plane_surface([boundary])
    cad.synchronize()


if __name__ == '__main__':
    gen_unit_square()
    gmsh.write("unit_square.msh")