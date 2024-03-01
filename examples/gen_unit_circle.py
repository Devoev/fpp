import gmsh

from gmsh_model import gmsh_model

cad = gmsh.model.occ
msh = gmsh.model.mesh


@gmsh_model("unit_circle", dim=2, finalize=False, options={"Mesh.MeshSizeFactor": 0.3, "Mesh.MeshSizeMax": 0.3})
def gen_unit_circle():
    """Creates a mesh of a unit circle."""

    p = cad.add_point(0,0,0)
    c = cad.add_circle(0,0,0,1)
    boundary = cad.add_curve_loop([c])
    omega = cad.add_plane_surface([boundary])

    cad.synchronize()
    msh.embed(0, [p], 2, omega)
    cad.synchronize()


if __name__ == '__main__':
    gen_unit_circle()
    gmsh.write("unit_circle.msh")