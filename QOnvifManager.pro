TEMPLATE = subdirs

SUBDIRS += QOnvifManger QOnvifMangerTester

QOnvifManger.file = src/QOnvifManager.pro
QOnvifMangerTester.file = test/QOnvifManagerTester.pro

QOnvifMangerTester.depends = QOnvifManger
