//=====================================================================
//
// test_mxml.c - 
//
// Created by wwq on 2023/03/29
// Last Modified: 2023/03/29 10:52:52
//
//=====================================================================
#include <mxml.h>


int main(int argc, char **argv)
{
    mxml_node_t *xml;
    mxml_node_t *node;
    xml = mxmlLoadString(NULL, "<root><foo>bar</foo></root>", MXML_TEXT_CALLBACK);
    node = mxmlFindElement(xml, xml, "foo", NULL, NULL, MXML_DESCEND);

    printf("%s\n", mxmlGetText(node, NULL));

    mxmlDelete(xml);

    return 0;
}
