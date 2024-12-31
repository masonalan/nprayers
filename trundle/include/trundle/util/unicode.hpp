//
// Created by James Pickering on 12/23/24.
//

#pragma once

#include <string>

namespace trundle {

struct String {
    static const std::string Space;
};

struct Unicode {
    static const std::string Block;
    static const std::string BlockLeft;
    static const std::string BlockRight;
    static const std::string BlockTop;
    static const std::string BlockBottom;
    static const std::string BlockMediumShade;
    static const std::string BlockLightShade;
    static const std::string Square;
    static const std::string LineVert;
    static const std::string LineHoriz;
    static const std::string LineHorizDouble;
    static const std::string CornerTopRight;
    static const std::string CornerTopRightHorizDouble;
    static const std::string CornerTopLeft;
    static const std::string CornerTopLeftHorizDouble;
    static const std::string CornerBottomRight;
    static const std::string CornerBottomLeft;
    static const std::string ArrowRightDouble;
    static const std::string Percent;
    static const std::string Option;
    static const std::string ArrowUp;
    static const std::string ArrowDown;
    static const std::string ArrowUpOutline;
    static const std::string ArrowLeft;
    static const std::string ArrowRight;
    static const std::string LineHorizDown;
    static const std::string LineHorizUp;
    static const std::string LineForwardSlash;
    static const std::string LineBackSlash;
    static const std::string LineVertLeft;
    static const std::string LineVertRight;
    static const std::string Return;
    static const std::string ArrowRightVertLine;
};

}
