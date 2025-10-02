# Changelog

All notable changes to the Autonomous Shopping Cart project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

### Planned
- Obstacle avoidance using ultrasonic sensors
- Battery level monitoring and low battery warning
- Emergency stop button functionality
- Mobile app for remote monitoring

---

## [1.0.0] - 2023-01-XX

### Added
- Initial release of Autonomous Shopping Cart system
- Pixy2 camera integration for color-based person tracking
- Arduino Uno control system with L298N motor driver
- SPI communication between Pixy2 and Arduino
- Real-time object detection and following algorithm
- Differential drive control for left/right turning
- Dead zone implementation to prevent oscillation
- Serial monitor debugging output
- Comprehensive documentation:
  - README with project overview
  - User manual with operating instructions
  - Setup guide for quick start
  - Circuit diagrams and wiring instructions
  - Bill of materials with pricing
  - Contributing guidelines
- MIT License for open source distribution

### Features
- Color signature-based person tracking
- Autonomous following at 30-100 cm distance
- Adjustable following speed and sensitivity
- Safe distance maintenance
- Real-time position normalization
- PWM motor speed control

### Hardware
- Arduino Uno Rev 3 (ATmega328P)
- Pixy2 CMUcam5 smart vision sensor
- L298N dual H-bridge motor driver
- 4x DC geared motors with cart chassis
- 7-12V battery power system

### Known Issues
- May confuse multiple objects with same color signature
- Limited response to sharp directional changes
- Performance affected by lighting conditions
- No obstacle avoidance capability
- Basic 2-wheel differential drive (limited maneuverability)

### Documentation
- Full project report included
- Academic honesty statement signed by all team members
- Bill of materials with local pricing (Bangladesh)
- Experimental data collected and analyzed

### Performance Metrics
- Following distance: 30-100 cm
- Response time: 1-2 seconds
- Operating time: 30-60 minutes (battery dependent)
- Maximum speed: ~0.3 m/s
- Detection accuracy: Good in controlled lighting

---

## Version History

### Version Numbering Scheme

- **MAJOR** version: Incompatible API/hardware changes
- **MINOR** version: Backwards-compatible functionality additions
- **PATCH** version: Backwards-compatible bug fixes

Examples:
- `1.0.0` - Initial release
- `1.1.0` - Added obstacle avoidance (new feature)
- `1.1.1` - Fixed motor direction bug (bug fix)
- `2.0.0` - Changed to I2C communication (breaking change)

---

## Future Releases (Roadmap)

### [1.1.0] - Planned
**Focus: Safety and Reliability**

#### To Add
- [ ] Emergency stop button hardware and code
- [ ] Battery voltage monitoring
- [ ] Low battery warning (LED/buzzer)
- [ ] Ultrasonic sensor for obstacle detection
- [ ] Improved error handling in code
- [ ] Watchdog timer implementation

#### To Fix
- [ ] Sharp turn response improvement
- [ ] Multiple object handling logic
- [ ] Serial output optimization

### [1.2.0] - Planned
**Focus: Enhanced Navigation**

#### To Add
- [ ] PID controller for smoother following
- [ ] Distance-based speed adjustment
- [ ] Improved path prediction
- [ ] Multi-signature tracking support
- [ ] Configurable following modes (close/far)

### [2.0.0] - Planned
**Focus: Advanced Features**

#### To Add
- [ ] Machine learning-based person detection
- [ ] RFID/NFC product scanning
- [ ] Weight sensor integration
- [ ] LCD display for cart status
- [ ] Bluetooth/Wi-Fi connectivity
- [ ] Mobile app integration

---

## Template for Future Releases

```markdown
## [Version] - YYYY-MM-DD

### Added
- New features added to the project

### Changed
- Changes in existing functionality

### Deprecated
- Features that will be removed in future versions

### Removed
- Features removed in this version

### Fixed
- Bug fixes

### Security
- Security vulnerability fixes
```

---

## Contributors

### Version 1.0.0
- **Joydip Chakraborty** (1906117) - Hardware assembly
- **Abdullah Al Numan** (1906121) - Hardware assembly  
- **K M Fahim Asif** (1906122) - Software development
- **Md Galib Mahmud Sharif** (1906123) - Software development
- **SK Shahriar Iqbal** (1906124) - Hardware assembly
- **Anik Biswas** (1906125) - Software development

---

## Links

- [Repository](https://github.com/yourusername/autonomous-shopping-cart)
- [Issue Tracker](https://github.com/yourusername/autonomous-shopping-cart/issues)
- [Releases](https://github.com/yourusername/autonomous-shopping-cart/releases)

---

*For detailed commit history, see the [Git log](https://github.com/yourusername/autonomous-shopping-cart/commits/main).*
