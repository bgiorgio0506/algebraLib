#include "SystemResolver.h"
#include "math.h"

 bool SystemResolver::isLinearDependent(Vector v1, Vector v2) {
     if (v1.vLen != v2.vLen) return;

	 if (v1.vModuleSquared() == 0 || v2.vModuleSquared() == 0) return true;
	 else {
         double factor = 0;
         for (int i = 0; i < v1.vLen ; i++) {
             if (v1.v[i] != 0) {
                 factor = v2.v[i] / v1.v[i];
                 break;
             }
         }

         for (int i = 0; i <v1.vLen; i++){
             if (v1.v[i] * factor != v2.v[i])return false;
         }
         return true;
     }
}
