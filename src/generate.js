export function generate() {
  return {
    buildings: new Float32Array(
      [0, 20, 40].flatMap(offset => [
        0,
        offset,
        10,
        offset,
        10,
        10 + offset,
        0,
        10 + offset,
        10
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
