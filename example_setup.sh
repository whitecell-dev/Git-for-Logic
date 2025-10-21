#!/bin/bash
# Quick setup script for Git for Logic

echo "🎯 Setting up Git for Logic example..."

# Create project directory
mkdir -p git-logic-demo
cd git-logic-demo

# Install dependencies (you'll need to run this)
echo "📦 Install dependencies:"
echo "npm install js-yaml sqlite3"
echo ""

# Initialize repository  
node ../git-for-logic.js init

# Create example rules
mkdir -p rules
cat > logic-repo/rules/loan-approval.yaml << 'EOF'
metadata:
  name: "Loan Approval Rules"
  version: "1.0.0"
  description: "Simple loan approval logic"

rules:
  - name: "high_value_auto_approve"
    priority: 1
    when: "income > 100000 && credit_score > 750"
    then:
      status: "approved"
      loan_amount: "income * 5"
      rate: "0.025"
      reason: "High income, excellent credit"

  - name: "standard_approval"
    priority: 2
    when: "income > 50000 && credit_score > 650 && employment_years >= 2"
    then:
      status: "approved" 
      loan_amount: "income * 3"
      rate: "0.045"
      reason: "Meets standard criteria"

  - name: "manual_review"
    priority: 3
    when: "income > 40000 && credit_score > 600"
    then:
      status: "manual_review"
      reason: "Requires manual underwriting"

  - name: "auto_reject"
    priority: 4
    when: "credit_score < 600"
    then:
      status: "rejected"
      reason: "Credit score below minimum"

  - name: "default_review"
    priority: 999
    when: "true"
    then:
      status: "manual_review"
      reason: "Default case - manual review required"
EOF

# Create test data
mkdir -p data
cat > logic-repo/data/test-applicants.json << 'EOF'
[
  {
    "name": "Alice Johnson",
    "income": 120000,
    "credit_score": 780,
    "employment_years": 5
  },
  {
    "name": "Bob Smith", 
    "income": 65000,
    "credit_score": 680,
    "employment_years": 3
  },
  {
    "name": "Charlie Brown",
    "income": 45000,
    "credit_score": 620,
    "employment_years": 1
  },
  {
    "name": "Diana Wilson",
    "income": 35000,
    "credit_score": 580,
    "employment_years": 4
  }
]
EOF

# Create CSV version too
cat > data/test-applicants.csv << 'EOF'
name,income,credit_score,employment_years
Alice Johnson,120000,780,5
Bob Smith,65000,680,3
Charlie Brown,45000,620,1
Diana Wilson,35000,580,4
EOF

echo "✅ Example setup complete!"
echo ""
echo "🚀 Try these commands:"
echo "  cd git-logic-demo"
echo "  node ../git-for-logic.js execute loan-approval.yaml test-applicants.json 'Initial test'"
echo "  node ../git-for-logic.js log"
echo ""
echo "📁 Files created:"
echo "  rules/loan-approval.yaml - Example business rules"
echo "  data/test-applicants.json - Test data (JSON format)"
echo "  data/test-applicants.csv - Test data (CSV format)"
