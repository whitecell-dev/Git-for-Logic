#!/bin/bash
# test.sh

set -e

echo "🔨 Compiling..."
make clean
make

echo ""
echo "🧪 Testing initialization..."
./git-for-logic init

echo ""
echo "📁 Checking directory structure..."
if [ -d "logic-repo" ]; then
  echo "✅ logic-repo created"
  ls -la logic-repo/
else
  echo "❌ logic-repo not created"
  exit 1
fi

echo ""
echo "📋 Testing execution..."
./git-for-logic execute loan.yaml test.json "CALYX test run"

echo ""
echo "✅ All tests passed!"
