# Digital Transaction Fraud Detection System (C++)

> Enterprise-grade, rule-based fraud detection engine for digital payment systems. Built in pure C++ with a modular architecture, persistent storage, and compliance-style controls.

---

## 🚀 Overview

This project simulates a **real-world fintech fraud monitoring system** similar to those used by banks and digital wallets. It focuses on **deterministic, rule-based fraud detection** with enterprise controls such as:

* Risk scoring
* Automated account blocking
* Persistent audit trails
* Admin fraud monitoring
* Credit/Debit transaction flows

The project is developed with scalable design principles aligned with **Accenture-style enterprise delivery**.

---

## ✅ Key Features

### v1.0 – Core Rule-Based Fraud Detection (Stable)
- User account creation & secure login
- Debit-only transaction engine
- Rule-based fraud risk scoring (0–100)
- Automated account blocking
- File-based persistent storage (.dat)
- Case-insensitive geo-location validation

### v1.1 Phase 1 – Enterprise Transaction Foundation
- Credit + Debit transaction classification
- Fraud logic applied only to DEBIT transactions
- Upgraded audit log format with transaction type
- Enterprise-ready transaction object model

### v1.1 Phase 2 – Wallet Recharge & Trusted CREDIT Flow
- Wallet recharge functionality
- CREDIT transactions increase wallet balance
- CREDIT transactions bypass fraud checks
- Dual-entry audit logging (CREDIT & DEBIT)

### v1.1 Phase 3 – Security & Compliance Controls
- Masked password input (***** style)
- Immediate forced logout on fraud detection
- Rolling 24-hour daily transaction compliance limit (₹1,00,000)

### v1.1 Phase 4 – Admin Fraud Monitoring & Readable Audit Logs (Current)
- Admin login and monitoring dashboard
- View all users and blocked accounts
- View all transactions
- View suspicious (high-risk) transactions
- Human-readable timestamps for audit logs in admin dashboard

---

## v1.1 Enterprise Edition Status
With Phase 4 completed, v1.1 now represents a **full enterprise-grade fraud detection and compliance system** with user, admin, security, audit, and regulatory controls integrated.


---

## 🧠 Fraud Detection Rules

Risk Score = Amount Risk + Frequency Risk + Geo Risk

| Rule              | Description              | Risk |
| ----------------- | ------------------------ | ---- |
| High Amount Spike | Debit > ₹50,000          | +40  |
| Frequency Burst   | ≥ 3 debits in 60 seconds | +30  |
| Geo Mismatch      | Non-INDIA location       | +30  |

**Blocking Threshold:** `Risk ≥ 70 → Account Blocked`

---

## 🏗️ Architecture

```
FraudDetectionSystem/
│
├── src/
│   ├── main.cpp
│   ├── User.cpp
│   ├── Transaction.cpp
│   ├── FraudEngine.cpp
│   ├── FileManager.cpp
│
├── include/
│   ├── User.h
│   ├── Transaction.h
│   ├── FraudEngine.h
│   ├── FileManager.h
│
├── data/
│   ├── users.dat
│   ├── transactions.dat
│
├── README.md
```

---

## ⚙️ Technology Stack

* **Language:** C++17
* **Paradigm:** Object-Oriented Programming (OOP)
* **Data Structures:** `map`, `vector`
* **Persistence:** File Handling (`fstream`)
* **Security Model:** Rule-based risk engine
* **Platform:** Cross-platform (Windows / Linux)

---

## 🛠️ Build & Run

### Prerequisites

* `g++` compiler
* Git

### Compilation

From the root directory:

```bash
g++ src/*.cpp -Iinclude -o fraud
```

### Run

```bash
./fraud
```

(Windows: `fraud` or `./fraud`)

---

## 🧪 How to Use

1. Create a new user
2. Login using credentials
3. Perform debit transactions
4. Observe fraud detection triggering
5. Recharge wallet (v1.1)
6. View blocked users as admin

---

## 🗃️ Data Storage Format

### `users.dat`

```
userId password balance blocked
```

### `transactions.dat`

```
userId amount location type timestamp
```

---

## 🔐 Security & Compliance Model

* Deterministic rule-based fraud detection
* Debit-only risk exposure
* Trusted credit inflow model
* Daily transaction ceiling
* Admin-level fraud visibility
* Full audit-log traceability

---

## 📈 Roadmap

* SQL database integration (MySQL/PostgreSQL)
* REST API layer (microservice-ready)
* Password hashing & encryption
* Admin export reports (CSV)
* Kafka-based transaction streaming

## 📄 License

This project is released under the **MIT License** for academic and demonstration purposes.
