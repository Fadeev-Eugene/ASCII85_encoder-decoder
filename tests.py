import unittest
import subprocess
import base64

class TestASCII85Encoder(unittest.TestCase):
    test_cases_encoder = [
        (b"", b""),                         
        (b"Hello", b"87cURDZ"),               
        (b"1234", b"0etOA"),                 
        (b"abcde", b"@:E_WAH"),             
        (b"Hello World!", b"87cURD]i,\"Ebo80") 
    ]

    def test_encoder_valid(self):
        for input_data, expected in self.test_cases_encoder:
            with self.subTest(input_data=input_data):
                process = subprocess.run(
                    ["./ascii85", "-e"],
                    input=input_data,
                    capture_output=True,
                    check=True
                )
                self.assertEqual(process.stdout, base64.a85encode(input_data, adobe=False))
                self.assertEqual(process.returncode, 0)

class TestASCII85Decoder(unittest.TestCase):
    test_cases_decoder = [
        (b"87cURDZ", b"Hello"),
        (b"0etOA", b"1234"),
        (b"@:E_WAH", b"abcde"),
        (b"87cURD]i,\"Ebo80", b"Hello World!"),
    ]

    def test_decoder_valid(self):
        for encoded_data, expected in self.test_cases_decoder:
            with self.subTest(encoded_data=encoded_data):
                process = subprocess.run(
                    ["./ascii85", "-d"],
                    input=encoded_data,
                    capture_output=True,
                    check=True
                )
                self.assertEqual(process.stdout, base64.a85decode(encoded_data, adobe=False))
                self.assertEqual(process.returncode, 0)

    def test_decoder_invalid(self):
        test_cases = [
            b"az",     
            b"www",
        ]
        
        for invalid_data in test_cases:
            with self.subTest(invalid_data=invalid_data):
                process = subprocess.run(
                    ["./ascii85", "-d"],
                    input=invalid_data,
                    capture_output=True
                )
                self.assertNotEqual(process.returncode, 0)


if __name__ == '__main__':
    unittest.main()
