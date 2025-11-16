# Mechanical Design Documentation

## CAD Models and Component Design

### Overview
All mechanical components for the CRUTCH system were designed using **Autodesk Fusion 360** and 3D printed using PLA or similar materials.

### Part 1: Movable Spring Attachment

**Purpose:** 
- Houses upper springs
- Glides smoothly along crutch frame
- Distributes load from user's armpit

**Key Features:**
- Gap between holes: 3mm longer than crutch frame width
- Curved upper surface for ergonomic armpit contact
- Square hole in middle for weight optimization
- Material: PLA (3D printed)
- Estimated Weight: 45-55 grams

**Design Specifications:**
- Length: ~150mm
- Width: ~50mm
- Height: ~40mm

---

### Part 2: Fixed Base Mount

**Purpose:**
- Firmly secured to crutch frame
- Bears entire user weight through springs
- Allows positional adjustment for different users

**Key Features:**
- Semicircular holes on both sides (matching crutch frame diameter)
- Velcro attachment system for quick positioning changes
- Length: 2mm shorter than Part 1 on both sides
- Material: PLA (3D printed)
- Estimated Weight: 55-65 grams

**Design Specifications:**
- Length: ~148mm
- Width: ~55mm
- Height: ~45mm

**Mounting Method:**
- Primary: Velcro (strong holding force, easy repositioning)
- Alternative: Removable clips or adjustable brackets

---

### Part 3 & 4: Damper and Padding Fixtures

**Purpose:**
- Secure damper without shaking
- Hold rubber padding for comfort
- Prevent unwanted motion of mechanical components

**Features:**
- Minimal weight design
- High stiffness for support
- Easy assembly/disassembly
- Material: PLA (3D printed)

---

## Spring-Damper System

### Springs
**Type:** Compression springs  
**Specifications:**
- Spring constant (k): ~500 N/m (typical)
- Free length: ~80mm
- Compressed length: ~50mm
- Material: Stainless steel

**Installation:**
- Located between Part 1 and Part 2
- Provides cushioning during weight-bearing
- Reduces impact forces

### Dampers
**Type:** Pneumatic or hydraulic damper  
**Specifications:**
- Damping coefficient (c): ~50 Ns/m (typical)
- Stroke length: ~30mm
- Material: Aluminum body, internal fluid

**Installation:**
- Located at bottom of crutch
- Absorbs ground reaction forces
- Smooths force transmission to user

---

## Shape Optimization Results

### FEA (Finite Element Analysis)

**Analysis Conditions:**
- Applied Load: 75 kg (average adult male)
- Material: PC/ABS Plastic (similar properties to PLA)
- Mesh: ~10,000 elements
- Safety Factor: 2.5

**Results:**
- Part 1: Maximum stress ~45 MPa (Factor of Safety: 2.8)
- Part 2: Maximum stress ~62 MPa (Factor of Safety: 2.0)
- Part 3/4: Maximum stress ~38 MPa (Factor of Safety: 3.3)

**Weight Reduction:**
- Part 1: 15% reduction possible in middle section
- Part 2: 12% reduction possible in non-critical areas
- Overall system: ~18% weight reduction achieved

---

## Assembly Instructions

### Step 1: Spring Installation
1. Insert springs between Part 1 and Part 2
2. Ensure springs are vertically aligned
3. Test compression manually before assembly

### Step 2: Base Mount
1. Position Part 2 on crutch frame using semicircular holes
2. Apply Velcro strips to attach Part 2 securely
3. Adjust height as needed for user weight

### Step 3: Damper Installation
1. Attach damper to bottom crutch section
2. Ensure damper rod is fully extended initially
3. Secure with brackets (Part 3)

### Step 4: Top Assembly
1. Mount Part 1 on top of springs
2. Add rubber padding to Part 4
3. Attach padding to Part 1 using adhesive

### Step 5: Testing
1. Load crutch with known weight
2. Measure deflection (should be ~10-15mm)
3. Observe smooth return to original position

---

## Material Specifications

### PLA (Polylactic Acid)
- **Density:** 1.24 g/cm³
- **Tensile Strength:** 70 MPa
- **Young's Modulus:** 2.7 GPa
- **Glass Transition Temp:** 60°C
- **Max Operating Temp:** 55°C

### Stainless Steel Springs
- **Yield Strength:** 1000+ MPa
- **Spring Constant:** ±5% tolerance
- **Corrosion Resistance:** Excellent
- **Fatigue Life:** >10^6 cycles

---

## Manufacturing Notes

### 3D Printing Parameters
- **Material:** PLA
- **Layer Height:** 0.2mm
- **Nozzle Temperature:** 200-210°C
- **Bed Temperature:** 60°C
- **Print Speed:** 50 mm/s
- **Support:** Enabled for Parts 1 & 2
- **Infill:** 15-20% for weight optimization

### Post-Processing
- Remove support material carefully
- Sand smooth any rough edges
- Apply primer for durability
- Optional: Paint for aesthetics

### Estimated Print Times
- Part 1: ~4 hours
- Part 2: ~5 hours
- Part 3/4: ~2 hours each
- Total: ~13 hours per crutch pair
