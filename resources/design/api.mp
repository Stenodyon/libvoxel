_metauml_defaults_mp := 1; % avoid loading metauml_defaults.mp
string metauml_defaultFont;
metauml_defaultFont  := "fvmr8r";
string metauml_defaultFontOblique;
metauml_defaultFontOblique  := "fvmro8r";
string metauml_defaultFontBold;
metauml_defaultFontBold  := "fvmb8r";
string metauml_defaultFontBoldOblique;
metauml_defaultFontBoldOblique  := "fvmbo8r";

input metauml;
beginfig(1);
    Class.Vec("Vec3<T>")(
        "+x: T",
        "+y: T",
        "+z: T")(
        "+operator+(other: const Vec3<T> &) const : Vec3<T>",
        "+operator+=(other: const Vec3<T> &) : Vec3<T> &",
        "+operator-() : Vec3<T> &",
        "+operator-(other: const Vec3<T> &) const : Vec3<T>",
        "+operator-=(other: const Vec3<T> &) : Vec3<T> &",
        "+operator*(value: int) const : Vec3<T>",
        "+operator*=(value: int) : Vec3<T> &",
        "+operator*(value: float) const : Vec3<T>",
        "+operator*=(value: float) : Vec3<T> &",
        "+operator*(value: double) const : Vec3<T>",
        "+operator*=(value: double) : Vec3<T> &",
        "+operator/(value: int) const : Vec3<T>",
        "+operator/=(value: int) : Vec3<T> &",
        "+operator/(value: float) const : Vec3<T>",
        "+operator/=(value: float) : Vec3<T> &",
        "+operator/(value: double) const : Vec3<T>",
        "+operator/=(value: double) : Vec3<T> &",
        "+dot(other: const Point &) const : T",
        "+cross(other: const Point &) const : Vec3<T>",
        "+norm() const : double",
    );
    classStereotypes.Vec("<<struct>>");

    Class.Point("Point = Vec3<int>")()();
    classStereotypes.Point("<<typedef>>");
    Point.info.iAttributeStack.top := 0;
    Point.info.iAttributeStack.bottom := 0;
    Point.info.iMethodStack.top := 0;
    Point.info.iMethodStack.bottom := 0;

    Class.Vector("Vector : Vec3<double>")()(
        "+normalize() : Vector &",
        "+normalized() const : Vector"
    );

    Class.BoxArea("BoxArea")(
        "+class iterator",
        "-lower: Point",
        "-upper: Point"
    )(
        "+BoxArea(corner1: const Point &, corner2: const Point &)",
        "+begin() : iterator",
        "+end() : iterator",
        "+lower_corner() const : Point",
        "+upper_corner() const : Point",
        "+size_x() const : int",
        "+size_y() const : int",
        "+size_z() const : int",
        "+inside(size: int) const : BoxArea",
        "+outside(size: int) const : BoxArea",
        "+face_xl() const : BoxArea",
        "+face_xu() const : BoxArea",
        "+face_yl() const : BoxArea",
        "+face_yu() const : BoxArea",
        "+face_zl() const : BoxArea",
        "+face_zu() const : BoxArea"
    );

    Class.BoxAreaIterator("BoxArea::iterator : std::iterator<std::input_iterator_tag, Point, Point, Point*, Point>")(
        "-start: Point",
        "-end: Point",
        "-current: Point"
    )(
        "+operator++() : BoxArea::iterator &",
        "+operator==(other : const BoxArea::iterator &) const : bool",
        "+operator!=(other : const BoxArea::iterator &) const : bool",
        "+operator*() const : Point"
    );

    Class.Graph("Graph")(
        "-nodes: std::vector<std::unique_ptr<GraphNode>>",
        "-buffers: std::vector<BufferNode*>"
    )(
        "+Graph()",
        "+add<NodeType, Args...>(Args... && args) : NodeType *",
        "+reset_buffers(void) : void",
        "+static FromFile(filename : std::string) : Graph"
    );

    Interface.GraphNode("GraphNode")();

    Interface.Node("Node<VoxelType> : GraphNode")(
        "+virtual get_voxel(pos : const Point &) = 0 : VoxelType");

    Class.Node_Perlin("PerlinNode : Node<int>")()(
        "-PerlinNode(seed: int, octave: int)");

    Class.Node_NOT("NOTNode : Node<bool>")(
        "-input: Node<bool>*")(
        "-NOTNode(input: Node<bool>*)");

    Class.Node_AND("ANDNode : Node<bool>")(
        "-lhs: Node<bool>*",
        "-rhs: Node<bool>*")(
        "-ANDNode(lhs: Node<bool>*, rhs: Node<bool>*)");

    Class.Node_OR("ORNode : Node<bool>")(
        "-lhs: Node<bool>*",
        "-rhs: Node<bool>*")(
        "-ORNode(lhs: Node<bool>*, rhs: Node<bool>*)");

    Class.Node_Mask("MaskNode<T> : Node<T>")(
        "-input: Node<T>*",
        "-mask: Node<bool>*")(
        "-MaskNode(input: Node<T>*, mask: Node<bool>*)");

    Note.Dots("SolidNode",
        "MultiplyNode",
        "ClampNode",
        "FillNode",
        "ProjectNode",
        "ErodeNode",
        "SquishNode",
        "CubeNode",
        "SphereNode",
        "CylinderNode",
        "NoiseNode",
        "FlipNode",
        "SymmetryNode",
        "DisplaceNode",
        "FilterNode",
        "EdgeDetectNode",
        "TranslateNode",
        "RotateNode",
        "ScaleNode",
        "OverlayNode",
        "BufferNode -> Memoizes the querried voxels instead of re-computing them"
    );

    Class.Mesh("Mesh")(
        "+vertices: std::vector<Vector>",
        "+normals: std::vector<Vector>",
        "+indices: std::vector<int>"
    )(
        "+Mesh(vertices: std::vector<Vector>, normals: std::vector<Vector>, indices: std::vector<int>)",
        "+static FromGraph(root: Node<bool>, area: BoxArea) : Mesh"
    );

    Class.TopLevel("TopLevel")()(
        "+export_obj(root: Node<?>, area: BoxArea, filename: std::string) : void",
        "+export_vox(root: Node<?>, area: BoxArea, filename: std::string) : void"
    );
    TopLevel.info.foreColor := (.9, .7, .7);

    topToBottom.right(10)(
        Node,
        Vec,
        BoxArea,
        Mesh
    );
    leftToRight(40)(
        BoxAreaIterator,
        BoxArea
    );
    topToBottom.right(10)(
        Point,
        Vector
    );
    leftToRight.top(40)(Point, Vec);
    topToBottom(40)(
        TopLevel,
        Graph,
        GraphNode,
        Node
    );
    leftToRight(40)(Node, Node_Perlin);
    topToBottom.left(10)(
        Node_Perlin,
        Node_NOT,
        Node_AND,
        Node_OR,
        Node_Mask,
        Dots);

    Package.voxelns("voxel")(
        Vec,
        Point,
        Vector,
        BoxArea,
        BoxAreaIterator,
        Graph,
        GraphNode,
        Node,
        Node_Perlin,
        Node_NOT,
        Node_AND,
        Node_OR,
        Node_Mask,
        Dots,
        Mesh,
        TopLevel
    );
    voxelns.info.foreColor := white;

    drawObjects(voxelns);

    link(dependency)(Graph.s .. GraphNode.n);
    item(iStereo)("<<friend>>")(obj.w = .5[GraphNode.n, Graph.s]);
    link(inheritance)(Node.n .. GraphNode.s);
    link(inheritance)(pathStepX(Node_Perlin.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_NOT.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_AND.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_OR.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_Mask.w, Node.e, -20));
    link(inheritance)(pathStepX(Dots.w, Node.e, -20));

    link(dependency)(pathHorizontal(Point.e, Vec.left));
    link(inheritance)(pathHorizontal(Vector.e, Vec.left));
    link(composition)(pathHorizontal(BoxAreaIterator.e, BoxArea.left));
endfig;
end
