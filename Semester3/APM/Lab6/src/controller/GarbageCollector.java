////package controller;
////
////import Model.Values.RefValue;
////import Model.Values.Value;
////
////import java.util.Collection;
////import java.util.List;
////import java.util.Map;
////import java.util.stream.Collectors;
////
////public class GarbageCollector {
////
////    public GarbageCollector() {
////    }
////
////    public Map<Integer, Value> unsafeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap) {
////        return heap.entrySet().stream()
////                .filter(e -> symTableAddr.contains(e.getKey()))
////                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
////    }
////
////    public List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
////        return symTableValues.stream()
////                .filter(v -> v instanceof RefValue)
////                .map(v -> ((RefValue) v).getAddress())
////                .collect(Collectors.toList());
////    }
////
////
////}
//
//package controller;
//
//import Model.PrgState;
//import Model.States.ProgState;
//import Model.Values.RefValue;
//import Model.Values.Value;
//
//import java.util.ArrayList;
//import java.util.List;
//import java.util.Map;
//import java.util.stream.Collectors;
//
//public class GarbageCollector {
//
//    public static void runGarbageCollector(List<PrgState> states) {
//        if (states.isEmpty()) {
//            return;
//        }
//        Map<Integer, Value> heap = states.get(0).getHeap().toMap();
//        List<Integer> activeAddresses = states.stream()
//                .flatMap(e -> GarbageCollector.getActiveAddressesForState(e).stream())
//                .toList();
//
//        heap.keySet().stream()
//                .filter(addr -> !activeAddresses.contains(addr))
//                .forEach(addr -> {
//                    try {
//                        states.get(0).getHeap().deallocate(addr);
//                    } catch (Exception ex) { // Replace with your specific exception class if needed
//                        throw new RuntimeException(ex);
//                    }
//                });
//    }
//
//    private static List<Integer> getActiveAddressesForState(PrgState state) {
//        return state.getSymTable().toMap().values().stream()
//                .filter(value -> value instanceof RefValue)
//                .map(value -> (RefValue) value)
//                .flatMap(refValue -> {
//                    List<Integer> addresses = new ArrayList<>();
//                    while (true) {
//                        if (refValue.getAddress() == 0) {
//                            break;
//                        }
//                        addresses.add(refValue.getAddress());
//                        Value nextValue;
//                        try {
//                            nextValue = state.getHeap().read(refValue.getAddress());
//                        } catch (Exception e) { // Replace with your specific exception class if needed
//                            throw new RuntimeException(e);
//                        }
//                        if (!(nextValue instanceof RefValue)) {
//                            break;
//                        }
//                        refValue = (RefValue) nextValue;
//                    }
//                    return addresses.stream();
//                }).collect(Collectors.toList());
//    }
//}
