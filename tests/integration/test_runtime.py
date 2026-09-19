import unittest
from tools.lib.host import compile_test
from tools.lib.config import ROOT


class RuntimeTests(unittest.TestCase):
    def test_c_resource_lifetimes(self):
        compile_test('runtime_test', [ROOT / 'tests/integration/runtime_test.c', ROOT / 'src/director/rogue_runtime.c'])
