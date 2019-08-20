const building0 = {
  ground_polygon: [[0, 0], [10, 0], [10, 10], [0, 10]],
  height: 10
};

const building1 = {
  ground_polygon: [[0, 20], [10, 20], [10, 30], [0, 30]],
  height: 10
};

const building2 = {
  ground_polygon: [[0, 40], [10, 40], [10, 50], [0, 50]],
  height: 10
};

const buildings = [building0, building1, building2];

export function generate() {
  return {
    buildings: new Float32Array(
      buildings.flatMap(building => [
        building.ground_polygon[0][0],
        building.ground_polygon[0][1],
        building.ground_polygon[1][0],
        building.ground_polygon[1][1],
        building.ground_polygon[2][0],
        building.ground_polygon[2][1],
        building.ground_polygon[3][0],
        building.ground_polygon[3][1],
        building.height
      ])
    ),

    setBuildings(buildings) {
      this.buildings = buildings;

      (this.listeners || []).forEach(listener => listener(this.buildings));
    },

    getBuildings() {
      return this.buildings;
    },

    onChange(listener) {
      this.listeners = this.listeners || [];
      this.listeners.push(listener);
    }
  };
}
