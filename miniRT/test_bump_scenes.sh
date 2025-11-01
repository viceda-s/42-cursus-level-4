#!/bin/sh
# Bump Mapping Test Script
# Tests all bump mapping scenes

cd "$(dirname "$0")/bonus" || exit 1

echo "╔══════════════════════════════════════════════════════════════╗"
echo "║         Bump Mapping Scene Tests                             ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo ""

PASS=0
FAIL=0

test_scene() {
    scene=$1
    name=$(basename "$scene")
    printf "%-35s: " "$name"

    if timeout 1 ./miniRT "$scene" >/dev/null 2>&1; then
        echo "✅ PASS"
        PASS=$((PASS + 1))
    else
        echo "❌ FAIL"
        FAIL=$((FAIL + 1))
    fi
}

# Test all bump scenes
test_scene "../scenes/bump_demo.rt"
test_scene "../scenes/bump_demo_clean.rt"
test_scene "../scenes/bump_all_objects.rt"
test_scene "../scenes/bump_vs_checker.rt"
test_scene "../scenes/test_bump.rt"
test_scene "../scenes/bump_test_final.rt"

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "Results: $PASS passed, $FAIL failed"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

