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
    Class.Point("Point")(
        "+x: int",
        "+y: int",
        "+z: int")(
        "+operator+(other: const Point &) const : Point",
        "+operator+=(other: const Point &) : Point &",
        "+operator-() : Point &",
        "+operator-(other: const Point &) const : Point",
        "+operator-=(other: const Point &) : Point &",
        "+operator*(value: int) const : Point",
        "+operator*=(value: int) : Point &",
        "+operator*(value: float) const : Point",
        "+operator*=(value: float) : Point &",
        "+operator*(value: double) const : Point",
        "+operator*=(value: double) : Point &",
        "+operator/(value: int) const : Point",
        "+operator/=(value: int) : Point &",
        "+operator/(value: float) const : Point",
        "+operator/=(value: float) : Point &",
        "+operator/(value: double) const : Point",
        "+operator/=(value: double) : Point &"
        );

    Class.Graph("Graph")(
        "-nodes: std::vector<std::unique_ptr<GraphNode>>",
        "-buffers: std::vector<BufferNode*>"
    )(
        "+add<NodeType, Args...>(Args... && args) : NodeType *",
        "+reset_buffers(void) : void"
    );

    Interface.GraphNode("GraphNode")();

    Interface.Node("Node<VoxelType> : GraphNode")(
        "+get_voxel(pos : const Point &) : VoxelType");

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
        "BufferNode -> Memoizes the querried voxels instead of re-computing them");

    Interface.Exporter("Exporter")(
        "+export(root: BaseNode*, c1: const Point &, c2: const Point &, filename: std::string) : void"
    );

    Class.OBJExporter("OBJExporter : Exporter")()();
    Class.VoxExporter("VoxExporter : Exporter")()();

    %leftToRight.top(10)(Point, Graph);
    topToBottom.right(40)(Node, Point);
    topToBottom(40)(Graph, GraphNode, Node);
    leftToRight(40)(Node, Node_Perlin);
    topToBottom.left(10)(
        Node_Perlin,
        Node_NOT,
        Node_AND,
        Node_OR,
        Node_Mask,
        Dots);

    Exporter.ne = Dots.sw - (40, 40);
    leftToRight(40)(Exporter, OBJExporter);
    topToBottom(10)(
        OBJExporter,
        VoxExporter
    );

    Package.voxelns("voxel")(
        Point,
        Graph,
        GraphNode,
        Node,
        Node_Perlin,
        Node_NOT,
        Node_AND,
        Node_OR,
        Node_Mask,
        Dots,
        Exporter,
        OBJExporter,
        VoxExporter
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

    link(inheritance)(pathStepX(OBJExporter.w, Exporter.e, -20));
    link(inheritance)(pathStepX(VoxExporter.w, Exporter.e, -20));
endfig;
end
