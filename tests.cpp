#include <gtest/gtest.h>
#include <sstream>
#include "encoder.h"
#include "decoder.h"

TEST(ASCII85Test, EncodeEmptyInput) {
    std::istringstream input("");
    std::ostringstream output;
    
    encoder(input, output);
    
    EXPECT_TRUE(output.str().empty());
}

TEST(ASCII85Test, EncodeSingleZeroBlock) {
    std::string zeros(4, '\0');
    std::istringstream input(zeros);
    std::ostringstream output;
    
    encoder(input, output);
    
    EXPECT_EQ(output.str(), "z");
}

TEST(ASCII85Test, EncodeBasicText) {
    std::istringstream input("test");
    std::ostringstream output;
    
    encoder(input, output);
    
    EXPECT_EQ(output.str(), "FCfN8");
}

TEST(ASCII85Test, EncodePartialBlock) {
    std::istringstream input("hi");
    std::ostringstream output;
    
    encoder(input, output);
    
    EXPECT_EQ(output.str(), "BP@");
}

TEST(ASCII85Test, DecodeEmptyInput) {
    std::istringstream input("");
    std::ostringstream output;
    
    decoder(input, output);
    
    EXPECT_TRUE(output.str().empty());
}

TEST(ASCII85Test, DecodeSingleZ) {
    std::istringstream input("z");
    std::ostringstream output;
    
    decoder(input, output);
    
    EXPECT_EQ(output.str(), std::string("\0\0\0\0", 4));
}

TEST(ASCII85Test, DecodeBasicText) {
    std::istringstream input("FCfN8");
    std::ostringstream output;
    
    decoder(input, output);
    
    EXPECT_EQ(output.str(), "test");
}

TEST(ASCII85Test, DecodePartialBlock) {
    std::istringstream input("BP@");
    std::ostringstream output;
    
    decoder(input, output);
    
    EXPECT_EQ(output.str(), "hi");
}

TEST(ASCII85Test, EncodeDecodeRoundtrip) {
    const std::string original = "Hello, World!";
    std::istringstream input(original);
    std::ostringstream encoded;
    
    encoder(input, encoded);
    
    std::istringstream encoded_input(encoded.str());
    std::ostringstream decoded;
    
    decoder(encoded_input, decoded);
    
    EXPECT_EQ(decoded.str(), original);
}

TEST(ASCII85Test, DecodeInvalidCharacter) {
    std::istringstream input("FCfN\x01");
    std::ostringstream output;
    
    EXPECT_THROW(decoder(input, output), std::runtime_error);
}

TEST(ASCII85Test, DecodeZInMiddleOfBlock) {
    std::istringstream input("FCzN8");
    std::ostringstream output;
    
    EXPECT_THROW(decoder(input, output), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
