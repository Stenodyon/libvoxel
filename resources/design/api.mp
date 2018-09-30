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

    Interface.Node("Node<VoxelType>")(
        "+get_voxel(pos : const Point &) : VoxelType");

    Class.Node_Perlin("PerlinNode : Node<int>")()(
        "+PerlinNode(seed: int, octave: int)");

    Class.Node_Complement("ComplementNode : Node<bool>")(
        "-input: Node<bool>*")(
        "+ComplementNode(input: Node<bool>*)");

    Class.Node_AND("ANDNode : Node<bool>")(
        "-lhs: Node<bool>*",
        "-rhs: Node<bool>*")(
        "+ANDNode(lhs: Node<bool>*, rhs: Node<bool>*)");

    Class.Node_OR("ORNode : Node<bool>")(
        "-lhs: Node<bool>*",
        "-rhs: Node<bool>*")(
        "+ORNode(lhs: Node<bool>*, rhs: Node<bool>*)");

    Class.Node_Mask("MaskNode<T> : Node<T>")(
        "-input: Node<T>*",
        "-mask: Node<bool>*")(
        "+MaskNode(input: Node<T>*, mask: Node<bool>*)");

    % TODO: SolidNode, MultiplyNode, ClampNode, FillNode, ProjectNode,
    %       ErodeNode, SquishNode, CubeNode, SphereNode, CylinderNode,
    %       NoiseNode, FlipNode, SymmetryNode, DisplaceNode, FilterNode,
    %       EdgeDetectNode, TranslateNode, RotateNode, ScaleNode, OverlayNode

    leftToRight.top(10)(Point, Node);
    leftToRight(40)(Node, Node_Perlin);
    topToBottom.left(10)(
        Node_Perlin,
        Node_Complement,
        Node_AND,
        Node_OR,
        Node_Mask);

    Package.voxelns("voxel")(
        Point,
        Node,
        Node_Perlin,
        Node_Complement,
        Node_AND,
        Node_OR,
        Node_Mask);
    voxelns.info.foreColor := white;

    drawObjects(voxelns);

    link(inheritance)(pathStepX(Node_Perlin.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_Complement.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_AND.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_OR.w, Node.e, -20));
    link(inheritance)(pathStepX(Node_Mask.w, Node.e, -20));
endfig;
end
