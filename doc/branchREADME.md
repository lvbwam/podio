A new datamodel which can store structs with two integers are added to datalayoutcopy.yaml:

    ExampleWithStruct:
     Description: "Datatype with a struct member"
     Author: "Ali Fatemi"
     Members:
       - NotSoSimpleStruct mystruct // component that contains an struct
