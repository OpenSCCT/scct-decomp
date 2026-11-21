"""The ByteMatch export names each function so the project page can find its source."""

import unittest

from bytematch import source_name, virtual_address


class NamingTests(unittest.TestCase):
    def test_decorated_c_symbols_name_their_source_function(self):
        self.assertEqual(source_name("_SND_fn_vSetCurrentLanguage@4"), "SND_fn_vSetCurrentLanguage")
        self.assertEqual(source_name("@destroy_child@4"), "destroy_child")
        self.assertEqual(source_name("_memcpy"), "memcpy")
        self.assertIsNone(source_name("??1UClass@@UAE@XZ"))

    def test_virtual_address_follows_the_section_mapping(self):
        target = dict(image=dict(executable_sections=[dict(offset=0x400, size=0x1000, address=0x10001000)]))
        self.assertEqual(virtual_address(target, 0x480), 0x10001080)
        with self.assertRaises(ValueError):
            virtual_address(target, 0x2000)


if __name__ == "__main__":
    unittest.main()
